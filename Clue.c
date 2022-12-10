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
	int init; int display; H3Handle btnQuit; bool exit; H3Handle h3; H3Handle scn; float px; float py;

} ClueComponent_Properties;




void ClueComponent_Terminate(void* properties)
{

	free(properties);
}



void* ClueComponent_CreateProperties(H3Handle scn, H3Handle h3)
{
	ClueComponent_Properties* properties = malloc(sizeof(ClueComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = 0;
	properties->h3 = h3;
	properties->display = 0;
	properties->scn = scn;
	

	return properties;
}

void UpClue(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	ClueComponent_Properties* p = (ClueComponent_Properties*)properties;

	if (p->init == 0)
	{
		p->init = 1;
		p->btnQuit = H3_Object_Create(p->scn, "btnQuit", object);
		H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/CluePaper.png", A_Center+A_Middle));
		H3_Object_AddComponent(p->btnQuit, SPRITECOMPONENT_CREATE("assets/btnQuit1.png", A_Center + A_Middle));
		
		H3_Object_SetTranslation(object, 1000, 500);
		H3_Object_SetTranslation(p->btnQuit, 850, -450);
		H3_Object_SetEnabled(object, false);
	}
	H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
	p->exit = H3_Button(p->h3, SpriteComponent_GetTextureEx(p->btnQuit), p->px+850, p->py-450, A_Center + A_Middle);
	if (p->display == 1)
	{
		H3_Object_SetEnabled(object, true);
	}
	if (p->exit)
	{
		printf("affiche rien");
		p->display = 0;
		H3_Object_SetEnabled(object, false);
	}

}