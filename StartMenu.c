#include "StartMenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include<components/spritecomponent.h>
#include <components/cameracomponent.h>
#include <components/maplayercomponent.h>
#include <components/textcomponent.h>
#include "Inventory.h"


typedef struct
{
	float init; 
	H3Handle scn;
	H3Handle h3;
	H3Handle mapStartMenu;
	H3Handle camStartMenu;
	H3Handle map_test;


} MCComponent_Properties;


void MCComponent_Terminate(void* properties)
{

	free(properties);
}



void* MCComponent_CreateProperties(H3Handle scn, H3Handle h3)
{
	MCComponent_Properties* properties = malloc(sizeof(MCComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scn = scn;
	properties->init = 0;
	properties->h3 = h3;
	properties->mapStartMenu = H3_Object_Create(properties->scn, "mapStartMenu", NULL);
	properties->camStartMenu = H3_Object_Create(properties->scn, "camStartMenu", NULL);

	return properties;
}



void UpMC(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

	MCComponent_Properties* p = (MCComponent_Properties*)properties;
	if (p->init == 0)
	{
		p->init = 1;

		
		H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/floutage_menu.png", A_Center+A_Middle));
		p->map_test = H3_Map_Load("assets/map_test.tmx");
		H3_Object_AddComponent(p->mapStartMenu, MAPLAYERCOMPONENT_CREATE(p->map_test, "Layer1"));
		H3_Map_Draw(p->h3, p->map_test);
		H3_Object_AddComponent(p->camStartMenu, CAMERACOMPONENT_CREATE(120, 120));
		H3_Object_SetTranslation(p->camStartMenu, 20, 20);
		
	}

	

}

