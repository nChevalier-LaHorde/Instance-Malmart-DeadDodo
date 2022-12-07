#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include<components/spritecomponent.h>
#include <components/cameracomponent.h>
#include <components/textcomponent.h>
#include "Inventory.h"


typedef struct
{
	float px; float py; int sx; int sy; float vx; float vy; float mouvx; float mouvy; float speed_max; float norme;
	float camx; float camy; int playerOnCollision; int init; H3Handle objTouch; int nbrObjTouch;



} PlayerComponent_Properties;


void PlayerComponent_Terminate(void* properties)
{

	free(properties);
}



void* PlayerComponent_CreateProperties()
{
	PlayerComponent_Properties* properties = malloc(sizeof(PlayerComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");



	properties->py = 0;
	properties->px = 0;
	properties->sx = 0;
	properties->sy = 0;
	properties->vx = 0;
	properties->mouvx = 0;
	properties->mouvy = 0;
	properties->speed_max = 200;
	properties->norme = 0;
	properties->camx = 0;
	properties->camy = 0;
	properties->playerOnCollision = 0;
	properties->init = 0;
	properties->objTouch = NULL;
	properties->nbrObjTouch = 0;


	return properties;
}

void PlayerCol(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, PLAYERCOMPONENT_TYPEID);
	PlayerComponent_Properties* pe = (PlayerComponent_Properties*)(component->properties);
	if (col.other == NULL) {}


	pe->objTouch = col.other;
	pe->playerOnCollision = 1;

	pe->nbrObjTouch += 1;

}

void PlayerColLeave(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, PLAYERCOMPONENT_TYPEID);
	PlayerComponent_Properties* pe = (PlayerComponent_Properties*)(component->properties);


	if (pe->nbrObjTouch < 2)
	{
		pe->objTouch = NULL;
		pe->playerOnCollision = 0;
	}

	pe->nbrObjTouch -= 1;
}

void UpPlayer(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

	PlayerComponent_Properties* p = (PlayerComponent_Properties*)properties;

	if (p->init == 0)
	{
		p->init = 1;
		H3_Object_AddComponent(object, INVENTORYCOMPONENT_CREATE(object));

	}


	H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);


	H3_Input_GetMousePos(h3, &p->sx, &p->sy);

	H3_Object_GetVelocity(object, &p->vx, &p->vy);





	if (H3_Input_IsMouseBtnDown(MB_Right))
	{

		H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
		H3_Input_GetMousePos(h3, &p->sx, &p->sy);
		p->mouvx = pow(((p->sx - p->px) / 30), 2);
		p->mouvy = pow(((p->sy - p->py) / 30), 2);
		p->norme = sqrt(pow(p->sx - p->px, 2) + pow(p->sy - p->py, 2));
		float vect = sqrt(p->mouvx + p->mouvy);

		H3_Object_SetVelocity(object, ((p->sx - p->px) / p->norme) * p->speed_max, ((p->sy - p->py) / p->norme) * p->speed_max);


	}
	else if (H3_Input_IsMouseBtnDown(MB_Right) == false)
	{
		H3_Object_SetVelocity(object, p->vx / 1.5, p->vy / 1.5);
	}

}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, PLAYERCOMPONENT_TYPEID, int, playerOnCollision);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, PLAYERCOMPONENT_TYPEID, H3Handle, objTouch);