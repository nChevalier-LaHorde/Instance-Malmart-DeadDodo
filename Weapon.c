#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "Weapon.h"
#include "Player.h"

typedef struct
{
	bool init;
	H3Handle weaponObj;
	float px; float py; // player X et Y
	int lastKeyPress;
} Weapon_Properties;

void* Weapon_CreateProperties(H3Handle cam, H3Handle scn)
{
	Weapon_Properties* properties = malloc(sizeof(Weapon_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = false;
	properties->weaponObj = H3_Object_Create2(scn, "weaponObj", NULL, 3);

	return properties;
}


void Weapon_Terminate(void* properties)
{
	free(properties);
}

void Weapon_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {
	Weapon_Properties* p = (Weapon_Properties*)properties;
	H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
	p->lastKeyPress = Player_GetlastKeyPressEx(object);
	if (!p->init)
	{
		p->init = true;
		H3_Object_AddComponent(p->weaponObj, ANIMATEDSPRITECOMPONENT_CREATE("assets/baguette.png", A_Middle + A_Center, 1, 1, false));
	}
	if (p->lastKeyPress == 0)
	{
		H3_Object_SetTranslation(p->weaponObj, p->px + 10, p->py + 5);
		H3_Object_SetRenderOrder(p->weaponObj, 3);
		AnimatedSpriteComponent_SetFlipYEx(p->weaponObj, false);
	}

	if (p->lastKeyPress == 1)
	{
		H3_Object_SetTranslation(p->weaponObj, p->px - 15, p->py + 5);
		H3_Object_SetRenderOrder(p->weaponObj, 2);
		AnimatedSpriteComponent_SetFlipYEx(p->weaponObj, true);
	}

	if (p->lastKeyPress == 2)
	{
		H3_Object_SetTranslation(p->weaponObj, p->px - 20, p->py + 2);
		H3_Object_SetRenderOrder(p->weaponObj, 3);
		AnimatedSpriteComponent_SetFlipYEx(p->weaponObj, true);
	}

	if (p->lastKeyPress == 3)
	{
		H3_Object_SetTranslation(p->weaponObj, p->px + 20, p->py + 2);
		H3_Object_SetRenderOrder(p->weaponObj, 2);
		AnimatedSpriteComponent_SetFlipYEx(p->weaponObj, false);
	}

}

void WeaponOnCollision(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, WEAPON_TYPEID);
	Weapon_Properties* pe = (Weapon_Properties*)(component->properties);
	if (col.other == NULL) {}

	else
	{
		printf("I hit this mother fucker \n\n\n\n\n");
	}

}