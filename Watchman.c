/*#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <components/spritecomponent.h>
#include <Watchman.h>
#include <RayCast.h>
#include <CheckPointIA.h>
#include <Player.h>

typedef struct
{
	H3Handle scene;
	float watchman_x;
	float watchman_y;
	float player_x;
	float player_y;
	float speed;
	bool init;
	bool hitPlayer;
	bool checkPoint;
	float distPlayer;
} Watchman_Properties;

void* Watchman_CreateProperties(H3Handle scene)
{
	Watchman_Properties* properties = malloc(sizeof(Watchman_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->scene = scene;
	properties->speed = 100;
	properties->init = true;
	properties->hitPlayer = false;
	properties->checkPoint = false;
	//properties->player_x = Player_Getplayer_xEx(H3_Object_Get(properties->scene, "player"));
	//properties->player_y = Player_Getplayer_yEx(H3_Object_Get(properties->scene, "player"));
	properties->distPlayer = sqrt(pow((properties->player_x - properties->watchman_x), 2) + pow((properties->player_y - properties->watchman_y), 2));
	return properties;
}


void Watchman_Terminate(void* properties)
{
	free(properties);
}

void Watchman_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {
	Watchman_Properties* props = (Watchman_Properties*)properties;

	if (props->init) {
		H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 32, 62, 0x22, false));
		H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/player.png", A_Center | A_Middle));
		H3_Object_SetTranslation(object, 900, 600);

		props->init = false;
	}


	printf("%d", props->checkPoint);
	if (props->distPlayer < 100) {

	}
}

void Watchman_Collision(H3Handle object, SH3Collision collision) {
	if (H3_Object_HasComponent(collision.other, NULL)) {

	}
	else if (H3_Object_HasComponent(collision.other, 0x10000001)) {
		printf("mort");
	}
}

void Watchman_Trigger(H3Handle object, SH3Collision collision) {
	SH3Component* component = H3_Object_GetComponent(object, 0x40000001);
	Watchman_Properties* props = (Watchman_Properties*)(component->properties);
	printf("a");
	if (H3_Object_HasComponent(collision.other, 0x30000001)) {
		printf("b");
		props->checkPoint = true;
	}
}

bool Watchman_RayCast(H3Handle scene, float vx, float vy, uint32_t id) {
	//H3Handle raycast = H3_Object_Create(scene, "raycast", NULL);
	//H3_Object_AddComponent(raycast);
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(Watchman, WATCHMAN_TYPEID, float, watchman_x);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Watchman, WATCHMAN_TYPEID, float, watchman_y);*/

#include "Watchman.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <AI.h>
#include <time.h>
#include<components/spritecomponent.h>
#include<components/textcomponent.h>
#include "Player.h"

typedef struct
{
	int index;
	H3Handle player; H3Handle scn;
	char buffer[100]; char bf[100];
	float timer; float px; float py; time_t t; float spawnx; float spawny;
	int life_z;
	int count_zk; int zombie_mc;
	bool ok;
} WatchmanComponent_Properties;




void WatchmanComponent_Terminate(void* properties)
{

	free(properties);
}



void* WatchmanComponent_CreateProperties(H3Handle player, H3Handle scn)
{
	WatchmanComponent_Properties* properties = malloc(sizeof(WatchmanComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->index = 0;
	properties->player = player;
	properties->timer = H3_GetTime();
	properties->scn = scn;
	properties->px = 0;
	properties->py = 0;
	properties->count_zk = 0;
	properties->zombie_mc = 0;
	properties->ok = true;

	srand(time(NULL));

	return properties;
}




void UpWatchman(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

	WatchmanComponent_Properties* p = (WatchmanComponent_Properties*)properties;
	H3_Transform_GetPosition(H3_Object_GetTransform(p->player), &p->px, &p->py);

	if (H3_GetTime() - p->timer > 3 && p->zombie_mc - p->count_zk < 200 && p->ok)
	{
		p->timer = H3_GetTime();
		printf("spawn");
		snprintf(p->buffer, 100, "zombie%d", p->index);
		H3Handle zombie = H3_Object_Create2(p->scn, p->buffer, NULL, 3);
		H3_Object_AddComponent(zombie, SPRITECOMPONENT_CREATE("assets/character.png", A_Middle | A_Center));
		H3_Object_AddComponent(zombie, AICOMPONENT_CREATE(p->scn, p->player, object));
		H3_Object_EnablePhysics(zombie, H3_BOX_COLLIDER(2, 50, 50, A_Top | A_Middle, false));

		H3_Transform_GetPosition(H3_Object_GetTransform(p->player), &p->px, &p->py);
		p->spawnx = 900;
		p->spawny = 900;
		/*if (sqrt(pow(p->px - p->spawnx, 2), pow(p->py - p->spawny, 2)) < 1000)
		{
			printf("change ^spawn\n");
			p->spawnx = rand() % 4750 + 32;
			p->spawny = rand() % 3150 + 32;
		}
		else if (sqrt(pow(p->px - p->spawnx, 2), pow(p->py - p->spawny, 2)) > 500)
		{
			H3_Object_SetTranslation(zombie, p->spawnx, p->spawny);
		}*/

		H3_Object_SetTranslation(zombie, p->spawnx, p->spawny);

		p->zombie_mc += 1;
		p->index += 1;
		p->ok = false;
	}



}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(WatchmanComponent, int, count_zk);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(WatchmanComponent, WATCHMANCOMPONENT_TYPEID, int, count_zk);