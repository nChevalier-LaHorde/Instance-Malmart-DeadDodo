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
	H3Handle monstere; H3Handle scn; H3Handle cam; float timerTiredness; float percentTiredness; float condition; int monstereEffect; int init;
	H3Handle paperClue; H3Handle h3; H3Handle fatigueBarOutline; H3Handle fatigueBarInline; float timeLagTiredness; float cX; float cY;

} ObjectComponent_Properties;




void ObjectComponent_Terminate(void* properties)
{

	free(properties);
}



void* ObjectComponent_CreateProperties(H3Handle scn, H3Handle h3, H3Handle cam)
{
	ObjectComponent_Properties* properties = malloc(sizeof(ObjectComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = 0;
	properties->scn = scn;
	properties->h3 = h3;
	properties->cam = cam;
	properties->monstere = H3_Object_Create(scn, "monstere", NULL);
	properties->paperClue = H3_Object_Create(scn, "paperClue", NULL);
	properties->fatigueBarInline = H3_Object_Create2(scn, "fatigueBarInline", NULL, 5);
	properties->fatigueBarOutline = H3_Object_Create2(scn, "fatigueBarOutline", NULL, 6);
	properties->timerTiredness = H3_GetTime()*10;
	properties->percentTiredness = 0;
	properties->monstereEffect = 0;
	properties->timeLagTiredness = 0;

	return properties;
}

void UpObject(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	ObjectComponent_Properties* p = (ObjectComponent_Properties*)properties;
	H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->cX, &p->cY);
	if (p->init == 0)
	{
		p->init = 1;
		H3_Object_AddComponent(p->monstere, MONSTERECOMPONENT_CREATE(object));
		H3_Object_AddComponent(p->fatigueBarInline, SPRITECOMPONENT_CREATE("assets/barreFatigue.png", A_Center+A_Left));
		H3_Object_AddComponent(p->fatigueBarOutline, SPRITECOMPONENT_CREATE("assets/contour_barre_fatigue.png", A_Center + A_Left));
		//H3_Object_AddComponent(p->paperClue, CLUECOMPONENT_CREATE(p->scn, p->h3, p->cam));
	}
	
	//printf("Time : %f\n",H3_GetTime());
	//printf("Time in game : %f\n", H3_GetTime() * 10);
	//printf("Time tiredness : %f\n", p->timerTiredness);
	if (H3_GetTime() - p->timerTiredness > 6 && p->monstereEffect == 0)
	{
		p->timerTiredness = H3_GetTime();
		p->percentTiredness += 10;
	}
	else if (H3_GetTime() - p->timerTiredness > 6 && p->monstereEffect == 1)
	{
		p->timerTiredness = H3_GetTime();
		p->percentTiredness += 2.5;
	}
	p->timeLagTiredness = 500 * p->percentTiredness / 100;

	H3_Object_SetTranslation(p->fatigueBarOutline, p->cX + 452, p->cY - 530);
	H3_Object_SetTranslation(p->fatigueBarInline, p->cX + p->timeLagTiredness+452, p->cY-530);
	//printf("Time in game with monstere : %f\n", H3_GetTime() * 10/4);
	printf("percent Tiredness : %f", p->percentTiredness);
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ObjectComponent, OBJECTCOMPONENT_TYPEID, int, monstereEffect);