#include "Clue.h"
#include "Object.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<components/spritecomponent.h>
#include <components/maplayercomponent.h>
#include <components/cameracomponent.h>

typedef struct
{
	int init; int display; H3Handle btnQuit; bool exit; H3Handle h3; H3Handle scn; float px; float py; H3Handle paper; H3Handle cam;

} ClueComponent_Properties;




void ClueComponent_Terminate(void* properties)
{

	free(properties);
}



void* ClueComponent_CreateProperties(H3Handle scn, H3Handle h3, H3Handle cam)
{
	ClueComponent_Properties* properties = malloc(sizeof(ClueComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = 0;
	properties->h3 = h3;
	properties->display = 0;
	properties->scn = scn;
	properties->cam = cam;
	

	return properties;
}

void UpClue(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	ClueComponent_Properties* p = (ClueComponent_Properties*)properties;
	H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->px, &p->py);// Get Camera position
	if (p->init == 0)
	{
		p->init = 1;
		p->paper = H3_Object_Create(p->scn, "paper", NULL);
		p->btnQuit = H3_Object_Create(p->scn, "btnQuit", NULL);

		H3_Object_AddComponent(p->paper, SPRITECOMPONENT_CREATE("assets/CluePaper.png", A_Center+A_Middle));
		H3_Object_AddComponent(p->btnQuit, SPRITECOMPONENT_CREATE("assets/btnQuit1.png", A_Center + A_Middle));
		

		H3_Object_SetEnabled(p->paper, false);
		H3_Object_SetEnabled(p->btnQuit, false);
	}
	H3_Object_SetTranslation(p->paper, p->px , p->py);
	H3_Object_SetTranslation(p->btnQuit, p->px+900, p->py-500 );
	//H3_Transform_GetPosition(H3_Object_GetTransform(p->btnQuit), &p->px, &p->py);//Get Coordonate of btnQuit 
	printf("X : %f\n", p->px + 900);
	printf("Y : %f\n", p->py -500);
	p->exit = H3_Button(p->h3, SpriteComponent_GetTextureEx(p->btnQuit),1860, 40, A_Center + A_Middle);
	if (p->display == 1)
	{
		H3_Object_SetEnabled(p->paper, true);
		H3_Object_SetEnabled(p->btnQuit, true);
	}
	if (p->exit)
	{
		printf("affiche rien");
		p->display = 0;
		H3_Object_SetEnabled(p->paper, false);
		H3_Object_SetEnabled(p->btnQuit, false);
	}

}
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ClueComponent, CLUECOMPONENT_TYPEID,int, display);