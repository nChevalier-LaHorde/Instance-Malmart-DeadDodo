#include "Monstere.h"
#include "Object.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <components/spritecomponent.h>
#include <components/maplayercomponent.h>
#include <components/cameracomponent.h>

typedef struct
{
	H3Handle monstere; int fatigue; H3Handle obj; int useMonstere; float timeUseMonstere; int oneTime;

} MonstereComponent_Properties;




void MonstereComponent_Terminate(void* properties)
{

	free(properties);
}



void* MonstereComponent_CreateProperties(H3Handle obj)
{
	MonstereComponent_Properties* properties = malloc(sizeof(MonstereComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->obj = obj;
	properties->useMonstere = 3;
	properties->oneTime = 0;


	return properties;
}

void UpMonstere(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	MonstereComponent_Properties* p = (MonstereComponent_Properties*)properties;
	if (p->useMonstere >= 1 && p->oneTime == 0)
	{
		p->oneTime = 1;
		ObjectComponent_SetmonstereEffectEx(p->obj, 1);
		p->timeUseMonstere = H3_GetTime();
	}
	else if (p->useMonstere >= 1 && H3_GetTime() - p->timeUseMonstere >= 6 * 4 + 1)
	{
		p->oneTime = 0;
		p->timeUseMonstere = 0;
		p->useMonstere -= 1;

	}
	if (p->useMonstere == 0)
	{
		ObjectComponent_SetmonstereEffectEx(p->obj, 0);
	}

	/*printf("Use monstere = %d /// One Time = %d\n", p->useMonstere, p->oneTime);*/
}