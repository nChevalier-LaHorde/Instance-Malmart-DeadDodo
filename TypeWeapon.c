#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "TypeWeapon.h"
#include "Player.h"
#include "Inventory.h"

typedef struct
{
	int a;
} Weapon_Properties;

void* TypeWeapon_CreateProperties()
{
	Weapon_Properties* properties = malloc(sizeof(Weapon_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");


	return properties;
}


void TypeWeapon_Terminate(void* properties)
{
	free(properties);
}

void NoneUpdate(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

}