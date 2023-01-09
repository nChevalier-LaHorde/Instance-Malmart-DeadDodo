#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "TypeExit2.h"


typedef struct
{
	int a;
} Exit2_Properties;

void* TypeExit2_CreateProperties()
{
	Exit2_Properties* properties = malloc(sizeof(Exit2_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");



	return properties;
}


void TypeExit2_Terminate(void* properties)
{
	free(properties);
}
