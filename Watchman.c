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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <components/spritecomponent.h>
#include "Watchman.h"
#include "AI.h"
#include "Player.h"

typedef struct
{
	H3Handle player;
	H3Handle scn;
	bool init;
	bool wave;

} Watchman_Properties;


void Watchman_Terminate(void* properties)
{
	free(properties);
}


void* Watchman_CreateProperties(H3Handle player, H3Handle scn)
{
	Watchman_Properties* properties = malloc(sizeof(Watchman_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	srand(time(NULL));

	properties->player = player;
	properties->scn = scn;
	properties->init = true;
	properties->wave = false;

	return properties;
}


void Watchman_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	Watchman_Properties* props = (Watchman_Properties*)properties;

	//spawn de 3 gardiens aux début du jeu
	if (props->init)
	{
		H3Handle watchman1 = H3_Object_Create2(props->scn, "watchman1", NULL, 3);
		H3_Object_AddComponent(watchman1, SPRITECOMPONENT_CREATE("assets/AI_Front.png", A_Middle | A_Center));
		H3_Object_AddComponent(watchman1, AI_CREATE(props->scn, props->player, object));
		H3_Object_EnablePhysics(watchman1, H3_BOX_COLLIDER(2, 24, 22, A_Top , false));
		H3_Object_SetTranslation(watchman1, 900, 900);

		H3Handle watchman2 = H3_Object_Create2(props->scn, "watchman2", NULL, 3);
		H3_Object_AddComponent(watchman2, SPRITECOMPONENT_CREATE("assets/AI_Front.png", A_Middle | A_Center));
		H3_Object_AddComponent(watchman2, AI_CREATE(props->scn, props->player, object));
		H3_Object_EnablePhysics(watchman2, H3_BOX_COLLIDER(2, 24, 22, A_Top, false));
		H3_Object_SetTranslation(watchman2, 900, 900);

		H3Handle watchman3 = H3_Object_Create2(props->scn, "watchman3", NULL, 3);
		H3_Object_AddComponent(watchman3, SPRITECOMPONENT_CREATE("assets/AI_Front.png", A_Middle | A_Center));
		H3_Object_AddComponent(watchman3, AI_CREATE(props->scn, props->player, object));
		H3_Object_EnablePhysics(watchman3, H3_BOX_COLLIDER(2, 24, 22, A_Top, false));
		H3_Object_SetTranslation(watchman3, 900, 900);

		props->init = false;
	}

	//spawn de 3 gardiens de plus lorsque le player a dévérouillé la porte
	if (props->wave) {

		H3Handle watchman4 = H3_Object_Create2(props->scn, "watchman4", NULL, 3);
		H3_Object_AddComponent(watchman4, SPRITECOMPONENT_CREATE("assets/AI_Front.png", A_Middle | A_Center));
		H3_Object_AddComponent(watchman4, AI_CREATE(props->scn, props->player, object));
		H3_Object_EnablePhysics(watchman4, H3_BOX_COLLIDER(2, 24, 22, A_Top, false));
		H3_Object_SetTranslation(watchman4, 900, 900);

		H3Handle watchman5 = H3_Object_Create2(props->scn, "watchman5", NULL, 3);
		H3_Object_AddComponent(watchman5, SPRITECOMPONENT_CREATE("assets/AI_Front.png", A_Middle | A_Center));
		H3_Object_AddComponent(watchman5, AI_CREATE(props->scn, props->player, object));
		H3_Object_EnablePhysics(watchman5, H3_BOX_COLLIDER(2, 24, 22, A_Top, false));
		H3_Object_SetTranslation(watchman5, 900, 900);

		H3Handle watchman6 = H3_Object_Create2(props->scn, "watchman6", NULL, 3);
		H3_Object_AddComponent(watchman6, SPRITECOMPONENT_CREATE("assets/AI_Front.png", A_Middle | A_Center));
		H3_Object_AddComponent(watchman6, AI_CREATE(props->scn, props->player, object));
		H3_Object_EnablePhysics(watchman6, H3_BOX_COLLIDER(2, 24, 22, A_Top, false));
		H3_Object_SetTranslation(watchman6, 900, 900);

		props->wave = true;
	}
}


H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Watchman, WATCHMAN_TYPEID, bool, wave);