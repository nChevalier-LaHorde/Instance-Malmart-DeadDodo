#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "TypeMonstere.h"
#include "Player.h"
#include "Inventory.h"

typedef struct
{
	int a;
} Monstere_Properties;

void* TypeMonstere_CreateProperties()
{
	Monstere_Properties* properties = malloc(sizeof(Monstere_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");


	return properties;
}


void TypeMonstere_Terminate(void* properties)
{
	free(properties);
}

void NoneUpdate2(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

}