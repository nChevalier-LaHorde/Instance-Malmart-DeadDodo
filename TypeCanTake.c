#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "TypeCanTake.h"
#include "Player.h"
#include "Inventory.h"

typedef struct
{
	int a;
} CanTake_Properties;

void* TypeCanTake_CreateProperties()
{
	CanTake_Properties* properties = malloc(sizeof(CanTake_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");


	return properties;
}


void TypeCanTake_Terminate(void* properties)
{
	free(properties);
}