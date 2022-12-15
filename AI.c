#include "AI.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include<components/spritecomponent.h>
#include "RayCast.h"
#include "Watchman.h"
#include "Player.h"

typedef struct
{
	int choose_dir;
	time_t t;
	float timer;
	int go;
	float zx; float zy; float rotate; float zvx; float zvy; char buffer[100]; int index;
	float px; float py;
	float dirx; float diry;
	H3Handle scn; H3Handle player; H3Handle zombie;
	int speed_bullet;
	float norme_b; int chase; int life_z; float speed_max; float speed; float norme; float timer_see; int first;
	float d_t; int d_t1; float timer_kick; float sound_play; H3Handle sound_z;



} AIComponent_Properties;


int notd = 0;

void AIComponent_Terminate(void* properties)
{

	free(properties);
}



void* AIComponent_CreateProperties(H3Handle scn, H3Handle player, H3Handle zombie)
{
	AIComponent_Properties* properties = malloc(sizeof(AIComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");


	properties->choose_dir = 0;
	srand(time(NULL));
	properties->timer = H3_GetTime();
	properties->go = 1;
	properties->index = 0;
	properties->scn = scn;
	properties->speed_bullet = 1000;
	properties->px = 1440 / 2;
	properties->py = 832 / 2;
	properties->chase = 0;
	properties->player = player;
	properties->life_z = 3;
	properties->zombie = zombie;
	properties->speed_max = 175;
	properties->speed = 100;
	properties->timer_see = H3_GetTime();
	properties->first = 0;
	properties->d_t1 = 0;
	properties->timer_kick = H3_GetTime();
	properties->sound_play = H3_GetTime();
	properties->sound_z = H3_Sound_Load("assets/sound_z.wav"); // Joseph Sardin

	return properties;
}

typedef struct
{
	float px; float py; int sx; int sy; float vx; float vy; float mouvx; float mouvy; float speed_max; float norme;
	float camx; float camy; float hc; float wc; float possx; float possy; float mw; float mh; float scalew; float scaleh;
	H3Handle cam; int life;

} PlayerComponent_Properties;

void ColAI(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, AICOMPONENT_TYPEID);
	AIComponent_Properties* p = (AIComponent_Properties*)(component->properties);

	if (col.other == NULL) {}

	else if (H3_Object_HasComponent(col.other, PLAYER_TYPEID) && H3_GetTime() - p->timer_kick > 1)
	{
		p->timer_kick = H3_GetTime();
		SH3Component* componentp = H3_Object_GetComponent(col.other, PLAYER_TYPEID);
		PlayerComponent_Properties* pp = (PlayerComponent_Properties*)(componentp->properties);

		pp->life -= 1;

	}



}

typedef struct
{
	H3Handle         Texture;
	EH3Anchor Anchor;
} SpriteComponent_Properties;

void UpAI(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	AIComponent_Properties* p = (AIComponent_Properties*)properties;

	if (H3_GetTime() - p->sound_play > 5)
	{
		p->sound_play = H3_GetTime();
		H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->zx, &p->zy);
		H3_Sound_PlaySpatialized(p->sound_z, 50, p->zx, p->zy, false);
	}



	if (p->life_z == 0 && p->d_t1 == 0)
	{
		p->d_t1 = 1;

		char buffer[100];
		snprintf(buffer, 100, "DEAD%f", H3_GetTime());
		H3Handle dead_z = H3_Object_Create2(p->scn, buffer, object, 0);

		H3_Object_AddComponent(dead_z, SPRITECOMPONENT_CREATE("assets/dead_z.png", A_Middle + A_Center));
		H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
		H3_Object_DisablePhysics(object);

		int okay = WatchmanComponent_Getcount_zkEx(p->zombie);
		WatchmanComponent_Setcount_zkEx(p->zombie, okay + 1);
		p->d_t = H3_GetTime();

	}

	if (p->d_t1 == 1)
	{
		if (H3_GetTime() - p->d_t > 10) { H3_Object_Destroy(object, true); }
	}

	if (p->d_t1 == 0)
	{
		if ((H3_GetTime() - p->timer > 10) || p->go == 1)
		{
			p->go = 0;
			p->timer = H3_GetTime();
			p->choose_dir = rand() % 4;

			H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->zx, &p->zy);
			if (p->choose_dir == 0)
			{
				H3_Object_SetVelocity(object, p->speed, 0);
				//p->dirx = 100+p->zx; p->diry = 0 + p->zy;
				p->rotate = atan2((p->zy + 0 - p->zy), (p->zx + 100 - p->zx));
				H3_Object_SetRotation(object, (p->rotate * (180 / 3.1415926535f) + 90));


			}
			else if (p->choose_dir == 1)
			{
				H3_Object_SetVelocity(object, -p->speed, 0);
				//p->dirx = -100 + p->zx; p->diry = 0 + p->zy;
				p->rotate = atan2((p->zy - p->zy), (p->zx - 100 - p->zx));
				H3_Object_SetRotation(object, (p->rotate * (180 / 3.1415926535f) + 90));
			}
			else if (p->choose_dir == 2)
			{
				H3_Object_SetVelocity(object, 0, p->speed);
				//p->dirx = 0 + p->zx; p->diry = 100 + p->zy;
				p->rotate = atan2((p->zy + 100 - p->zy), (p->zx + 0 - p->zx));
				H3_Object_SetRotation(object, (p->rotate * (180 / 3.1415926535f) + 90));

			}
			else if (p->choose_dir == 3)
			{
				H3_Object_SetVelocity(object, 0, -p->speed);
				//p->dirx = 0 + p->zx; p->diry = -100 + p->zy;
				p->rotate = atan2((p->zy - 100 - p->zy), (p->zx - p->zx));
				H3_Object_SetRotation(object, (p->rotate * (180 / 3.1415926535f) + 90));
			}
		}

		if (p->go == 2)
		{

			H3_Object_GetVelocity(object, &p->zvx, &p->zvy);

			H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->zx, &p->zy);
			H3_Transform_GetPosition(H3_Object_GetTransform(p->player), &p->px, &p->py);

			p->norme = sqrt(pow(p->px - p->zx, 2) + pow(p->py - p->zy, 2));


			H3_Object_SetVelocity(object, ((p->px - p->zx) / p->norme) * p->speed_max, ((p->py - p->zy) / p->norme) * p->speed_max);


			p->rotate = atan2((p->py - p->zy), (p->px - p->zx));
			H3_Object_SetRotation(object, (p->rotate * (180 / 3.1415926535f)) + 90);

		}


		H3_Object_GetVelocity(object, &p->zvx, &p->zvy);

		if ((p->zvx < 99 && p->zvy < 99) && (p->zvx > -99 && p->zvy > -99))
		{
			p->go = 1;
			p->chase = 0;
		}


		H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->zx, &p->zy);
		H3_Transform_GetPosition(H3_Object_GetTransform(p->player), &p->px, &p->py);


		if (sqrt(pow(p->px - p->zx, 2) + pow(p->py - p->zy, 2)) < 250)
		{
			////////////////////////////////////////////////////////////////////////////////
			snprintf(p->buffer, 100, "ray%f", p->index + H3_GetTime());
			H3Handle ray = H3_Object_Create2(p->scn, p->buffer, NULL, 3);
			if (notd == 0)

				//H3_Object_AddComponent(ray, SPRITECOMPONENT_CREATE("assets/fire.png", A_Middle | A_Center));
				H3_Object_AddComponent(ray, RAYCASTCOMPONENT_CREATE(object));







			if (p->chase == 1 && p->first == 0)
			{
				p->first = 1;
				p->go = 2;
				p->timer_see = H3_GetTime();
				p->chase = 0;
			}

			else if (H3_GetTime() - p->timer_see > 1 && p->first == 1)
			{
				p->first = 0;
				p->go = 0;
				p->timer = 20;
			}




			H3_Object_EnablePhysics(ray, H3_BOX_COLLIDER(2, 8, 8, A_Top | A_Middle, true));

			H3_Transform_GetPosition(H3_Object_GetTransform(p->player), &p->dirx, &p->diry);


			p->norme_b = sqrt(pow((p->dirx - p->zx), 2) + pow((p->diry - p->zy), 2));
			p->rotate = atan2((p->diry - p->zy), (p->dirx - p->zx));
			H3_Object_SetRotation(ray, (p->rotate * (180 / 3.1415926535f)) + 90);


			H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->zx, &p->zy);


			float degrees = atan2((p->diry - p->zy), (p->dirx - p->zx));
			float x2 = ((p->zx + 50 - p->zx) * cos(degrees)) - ((p->zy - p->zy) * sin(degrees)) + p->zx;
			float y2 = ((p->zx + 50 - p->zx) * sin(degrees)) + ((p->zy - p->zy) * cos(degrees)) + p->zy;
			H3_Object_SetTranslation(ray, x2, y2);

			H3_Object_SetVelocity(ray, ((p->dirx - p->zx) / p->norme_b) * p->speed_bullet, ((p->diry - p->zy) / p->norme_b) * p->speed_bullet);
			p->index += 1;
			//////////////////////////////////////////////////////////////////////////////
		}
	}
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(AIComponent, int, chase);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(AIComponent, AICOMPONENT_TYPEID, int, chase);