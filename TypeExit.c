#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "TypeExit.h"


typedef struct
{
	int a;
} Exit_Properties;

void* TypeExit_CreateProperties()
{
	Exit_Properties* properties = malloc(sizeof(Exit_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");



	return properties;
}


void TypeExit_Terminate(void* properties)
{
	free(properties);
}