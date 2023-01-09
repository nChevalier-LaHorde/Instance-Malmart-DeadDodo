#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <components/spritecomponent.h>
#include "AI.h"
#include "RayCast.h"
#include "Watchman.h"
#include "Player.h"
#include "WeaponHit.h"
#include "EndMenu.h"


typedef struct
{
	int choose_dir;
	float timer;
	int go;
	float zx; float zy; float rotate; float zvx; float zvy; char buffer[100]; int index;
	float px; float py;
	float dirx; float diry;
	H3Handle scn; H3Handle player; H3Handle watchman;
	int speed_bullet;
	float norme_b; int chase; float speed_max; float speed; float norme; float timer_see; int first;
	float sound_play; H3Handle sound_z;
	float w; float h;
	bool stun; float timer_stun; float stun_duration;

} AI_Properties;


void AI_Terminate(void* properties)
{
	free(properties);
}


void* AI_CreateProperties(H3Handle scn, H3Handle player, H3Handle watchman)
{
	AI_Properties* properties = malloc(sizeof(AI_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	srand(time(NULL));

	properties->choose_dir = 0;
	properties->timer = H3_GetTime();
	properties->go = 1;
	properties->index = 0;
	properties->scn = scn;
	properties->speed_bullet = 1000;
	properties->px = 1440 / 2;
	properties->py = 832 / 2;
	properties->chase = 0;
	properties->player = player;
	properties->watchman = watchman;
	properties->speed_max = 175;
	properties->speed = 100;
	properties->timer_see = H3_GetTime();
	properties->first = 0;
	properties->sound_play = H3_GetTime();
	properties->sound_z = H3_Sound_Load("assets/sound_z.wav");
	properties->stun = false;
	properties->timer_stun = H3_GetTime();
	properties->stun_duration = 5;

	return properties;
}


void AI_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	AI_Properties* props = (AI_Properties*)properties;

	//test si le gardien est étourdit
	if (props->stun) {
		H3_Object_GetVelocity(object, &props->zvx, &props->zvy);
		H3_Object_SetVelocity(object, props->zvx/1.06, props->zvy/1.06);

		//test si le gardien est étourdit depuis plus de stun_duration
		if (H3_GetTime() - props->timer_stun > props->stun_duration) {
			props->timer_stun = H3_GetTime();
			props->stun = false;
		}
	}

	//test si le gardien n'est pas étourdit
	if (!props->stun) {

		//permet au gardien de faire un bruit toutes les 5 secondes
		if (H3_GetTime() - props->sound_play > 5)
		{
			props->sound_play = H3_GetTime();
			H3_Transform_GetPosition(H3_Object_GetTransform(object), &props->zx, &props->zy);
			H3_Sound_PlaySpatialized(props->sound_z, 50, props->zx, props->zy, false);
		}

		// le gardien change de direction de déplacement aléatoirement toutes les 20 secondes
		if ((H3_GetTime() - props->timer > 20) || props->go == 1)
		{
			props->go = 0;
			props->timer = H3_GetTime();
			props->choose_dir = rand() % 4;

			H3_Transform_GetPosition(H3_Object_GetTransform(object), &props->zx, &props->zy);
			if (props->choose_dir == 0)
			{
				H3_Object_SetVelocity(object, props->speed, 0);
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Right.png", &props->w, &props->h));

			}
			else if (props->choose_dir == 1)
			{
				H3_Object_SetVelocity(object, -props->speed, 0);
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Left.png", &props->w, &props->h));
			}
			else if (props->choose_dir == 2)
			{
				H3_Object_SetVelocity(object, 0, props->speed);
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Front.png", &props->w, &props->h));

			}
			else if (props->choose_dir == 3)
			{
				H3_Object_SetVelocity(object, 0, -props->speed);
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Back.png", &props->w, &props->h));
			}
		}

		// si le gardien a detecté le joueur il se met à le poursuivre
		if (props->go == 2)
		{

			H3_Object_GetVelocity(object, &props->zvx, &props->zvy);

			H3_Transform_GetPosition(H3_Object_GetTransform(object), &props->zx, &props->zy);
			H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &props->px, &props->py);

			props->norme = sqrt(pow(props->px - props->zx, 2) + pow(props->py - props->zy, 2));


			H3_Object_SetVelocity(object, ((props->px - props->zx) / props->norme) * props->speed_max, ((props->py - props->zy) / props->norme) * props->speed_max);


			props->rotate = atan2((props->py - props->zy), (props->px - props->zx));
			if (props->rotate >= -0.8 && props->rotate <= 0.8) {
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Right.png", &props->w, &props->h));
			}
			else if (props->rotate > 2.3 || props->rotate < -2.3) {
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Left.png", &props->w, &props->h));
			}
			else if (props->rotate >= -2.3 && props->rotate < -0.8) {
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Back.png", &props->w, &props->h));
			}
			else if (props->rotate > 0.8 && props->rotate <= 2.3) {
				SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/AI_Front.png", &props->w, &props->h));
			}
		}


		H3_Object_GetVelocity(object, &props->zvx, &props->zvy);

		if ((props->zvx < 99 && props->zvy < 99) && (props->zvx > -99 && props->zvy > -99))
		{
			props->go = 1;
			props->chase = 0;
		}


		H3_Transform_GetPosition(H3_Object_GetTransform(object), &props->zx, &props->zy);
		H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &props->px, &props->py);

		//test si le player est suffisement proche pour faire un raycast
		if (sqrt(pow(props->px - props->zx, 2) + pow(props->py - props->zy, 2)) < 250)
		{
			snprintf(props->buffer, 100, "ray%f", props->index + H3_GetTime());
			H3Handle ray = H3_Object_Create2(props->scn, props->buffer, NULL, 3);
			H3_Object_AddComponent(ray, RAYCAST_CREATE(object));

			//test si le raycast a atteint le joueur
			if (props->chase == 1 && props->first == 0)
			{
				props->first = 1;
				props->go = 2;
				props->timer_see = H3_GetTime();
				props->chase = 0;
			}

			//test si le gardien a perdu le joueur de vue depuis plus de 1 seconde
			else if (H3_GetTime() - props->timer_see > 1 && props->first == 1)
			{
				props->first = 0;
				props->go = 0;
				props->timer = 20;
			}

			H3_Object_EnablePhysics(ray, H3_BOX_COLLIDER(2, 8, 8, A_Top | A_Middle, true));
			H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &props->dirx, &props->diry);

			//calculs pour effectuer le raycast
			props->norme_b = sqrt(pow((props->dirx - props->zx), 2) + pow((props->diry - props->zy), 2));
			float degrees = atan2((props->diry - props->zy), (props->dirx - props->zx));
			float x2 = ((props->zx + 50 - props->zx) * cos(degrees)) - ((props->zy - props->zy) * sin(degrees)) + props->zx;
			float y2 = ((props->zx + 50 - props->zx) * sin(degrees)) + ((props->zy - props->zy) * cos(degrees)) + props->zy;
			H3_Object_SetTranslation(ray, x2, y2);

			H3_Object_SetVelocity(ray, ((props->dirx - props->zx) / props->norme_b) * props->speed_bullet, ((props->diry - props->zy) / props->norme_b) * props->speed_bullet);
			props->index += 1;
		}
	}
}


void AI_Collision(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, AI_TYPEID);
	AI_Properties* props = (AI_Properties*)(component->properties);

	if (col.other == NULL)
	{

	}
	else if (H3_Object_HasComponent(col.other, PLAYER_TYPEID))
	{
		EndMenuComponent_SetplayerAliveEx(col.other, false);
	}
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(AI, int, chase);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(AI, AI_TYPEID, int, chase);