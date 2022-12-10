#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include "Inventory.h"
#include <Player.h>

typedef struct
{
	H3Handle cam;
	float player_x;
	float player_y;
	float speed;
	bool init;
	H3Handle objTouch;
	int playerOnCol;
	int nbrObjTouch;
} Player_Properties;

void* Player_CreateProperties(H3Handle cam)
{
	Player_Properties* properties = malloc(sizeof(Player_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->speed = 100;
	properties->cam = cam;
	properties->init = true;
	return properties;
}


void Player_Terminate(void* properties)
{
	free(properties);
}

void Player_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {
	Player_Properties* props = (Player_Properties*)properties;

	if (props->init) {
		H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 32, 32, 0x22, false));
		H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/player.png", A_Center | A_Middle));
		H3_Object_Translate(object, 960, 540);

		H3_Object_AddComponent(object, INVENTORYCOMPONENT_CREATE(object));

		props->init = false;
	}

	H3_Transform_GetPosition(H3_Object_GetTransform(object), &props->player_x, &props->player_y);
	H3_Object_SetTranslation(props->cam, props->player_x, props->player_y);

	H3_Object_SetVelocity(object, 0, 0);
	if (H3_Input_IsKeyDown(K_Right)) {
		H3_Object_AddVelocity(object, props->speed, 0);
	}
	if (H3_Input_IsKeyDown(K_Left)) {
		H3_Object_AddVelocity(object, -props->speed, 0);
	}
	if (H3_Input_IsKeyDown(K_Down)) {
		H3_Object_AddVelocity(object, 0, props->speed);
	}
	if (H3_Input_IsKeyDown(K_Up)) {
		H3_Object_AddVelocity(object, 0, -props->speed);
	}
}

void playerOnCollision(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, PLAYER_TYPEID);
	Player_Properties* pe = (Player_Properties*)(component->properties);
	if (col.other == NULL) {}


	pe->objTouch = col.other;
	pe->playerOnCol = 1;

	pe->nbrObjTouch += 1;

}

void playerOnCollisionLeave(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, PLAYER_TYPEID);
	Player_Properties* pe = (Player_Properties*)(component->properties);


	if (pe->nbrObjTouch < 2)
	{
		pe->objTouch = NULL;
		pe->playerOnCol = 0;
	}

	pe->nbrObjTouch -= 1;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO(Player, float, player_x);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(Player, float, player_y);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(Player, PLAYER_TYPEID, float, player_x);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, float, player_y);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, int, playerOnCol);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, H3Handle, objTouch);