#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "TypeKey.h"
#include "Player.h"
#include "Inventory.h"

typedef struct
{
	int a;
} Key_Properties;

void* TypeKey_CreateProperties()
{
	Key_Properties* properties = malloc(sizeof(Key_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");



	return properties;
}


void TypeKey_Terminate(void* properties)
{
	free(properties);
}

void UpKey(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

}