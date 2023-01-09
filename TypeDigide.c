#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "TypeDigide.h"


typedef struct
{
	int a;
} Digide_Properties;

void* TypeDigide_CreateProperties()
{
	Digide_Properties* properties = malloc(sizeof(Digide_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");



	return properties;
}


void TypeDigide_Terminate(void* properties)
{
	free(properties);
}

void UpDigide(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

}