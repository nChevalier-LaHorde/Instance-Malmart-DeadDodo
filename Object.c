#include "Object.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<components/spritecomponent.h>
#include <components/maplayercomponent.h>
#include <components/cameracomponent.h>
#include "Monstere.h"
#include "Clue.h"

typedef struct
{
	H3Handle monstere; H3Handle scn; float timerTiredness; float percentTiredness; float condition; int monstereEffect; int init;
	H3Handle paperClue; H3Handle h3;

} ObjectComponent_Properties;




void ObjectComponent_Terminate(void* properties)
{

	free(properties);
}



void* ObjectComponent_CreateProperties(H3Handle scn, H3Handle h3)
{
	ObjectComponent_Properties* properties = malloc(sizeof(ObjectComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = 0;
	properties->scn = scn;
	properties->h3 = h3;
	properties->monstere = H3_Object_Create(scn, "monstere", NULL);
	properties->paperClue = H3_Object_Create(scn, "paperClue", NULL);
	properties->timerTiredness = H3_GetTime()*10;
	properties->percentTiredness = 0;
	properties->monstereEffect = 0;


	return properties;
}

void UpObject(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	ObjectComponent_Properties* p = (ObjectComponent_Properties*)properties;
	
	if (p->init == 0)
	{
		p->init = 1;
		H3_Object_AddComponent(p->monstere, MONSTERECOMPONENT_CREATE(object));
		H3_Object_AddComponent(p->paperClue, CLUECOMPONENT_CREATE(p->scn, p->h3));
	}
	//printf("Time : %f\n",H3_GetTime());
	//printf("Time in game : %f\n", H3_GetTime() * 10);
	//printf("Time tiredness : %f\n", p->timerTiredness);
	if (H3_GetTime() - p->timerTiredness > 6 && p->monstereEffect == 0)
	{
		p->timerTiredness = H3_GetTime();
		p->percentTiredness += 10;
	}
	if (H3_GetTime() - p->timerTiredness > 6 && p->monstereEffect == 1)
	{
		p->timerTiredness = H3_GetTime();
		p->percentTiredness += 2.5;
	}
	//printf("Time in game with monstere : %f\n", H3_GetTime() * 10/4);
	//printf("percent Tiredness : %f", p->percentTiredness);
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ObjectComponent, OBJECTCOMPONENT_TYPEID, int, monstereEffect);