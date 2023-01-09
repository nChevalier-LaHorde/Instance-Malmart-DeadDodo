#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "WeaponHit.h"
#include "Player.h"
#include "Inventory.h"
#include "AI.h"

typedef struct
{
	int a;
	bool iAmOnCollisionWithAI;
}Hit_Properties;

void* Hit_CreateProperties()
{
	Hit_Properties* properties = malloc(sizeof(Hit_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");


	return properties;
}


void Hit_Terminate(void* properties)
{
	free(properties);
}

void hitOnCollision(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, HIT_TYPEID);
	Hit_Properties* p = (Hit_Properties*)(component->properties);

	if (col.other == NULL) {}
	else if (H3_Object_HasComponent(col.other, AI_TYPEID))
	{
		p->iAmOnCollisionWithAI = true;
	}
}

void hitOnCollisionLeave(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, HIT_TYPEID);
	Hit_Properties* p = (Hit_Properties*)(component->properties);

	p->iAmOnCollisionWithAI = false;

}
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Hit, HIT_TYPEID, bool, iAmOnCollisionWithAI);
