#include "Timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<components/spritecomponent.h>
#include <components/textcomponent.h>
#include <components/cameracomponent.h>
#include "Monstere.h"
#include "Object.h"
#include "Clue.h"


typedef struct
{
	 H3Handle scn; H3Handle cam; float timerTiredness; float percentTiredness; float condition; int monstereEffect; int init;
	 H3Handle fatigueBarOutline; H3Handle fatigueBarInline; float timeLagTiredness; float cX; float cY; H3Handle objectc; H3Handle font; char buffer_ts[100];
	 H3Handle texts; int hours; int min;

} TimerComponent_Properties;




void TimerComponent_Terminate(void* properties)
{

	free(properties);
}



void* TimerComponent_CreateProperties(H3Handle scn, H3Handle cam, H3Handle objectc)
{
	TimerComponent_Properties* properties = malloc(sizeof(TimerComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = 0;
	properties->scn = scn;
	properties->objectc = objectc;
	properties->cam = cam;
	properties->texts = H3_Object_Create2(scn, "texts", NULL, 10);
	properties->fatigueBarInline = H3_Object_Create2(scn, "fatigueBarInline", NULL, 5);
	properties->fatigueBarOutline = H3_Object_Create2(scn, "fatigueBarOutline", NULL, 6);

	properties->percentTiredness = 0;
	properties->monstereEffect = 0;
	properties->timeLagTiredness = 0;
	properties->font = H3_Font_Load("assets/Comfortaa-Regular.ttf");

	return properties;
}

void UpTimer(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	TimerComponent_Properties* p = (TimerComponent_Properties*)properties;
	p->monstereEffect = ObjectComponent_GetmonstereEffectEx(p->objectc);
	H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->cX, &p->cY);
		if (p->init == 0)
		{
			p->init = 1;
			H3_Object_AddComponent(p->fatigueBarInline, SPRITECOMPONENT_CREATE("assets/barreFatigue.png", A_Center + A_Left));
			H3_Object_AddComponent(p->fatigueBarOutline, SPRITECOMPONENT_CREATE("assets/contour_barre_fatigue.png", A_Center + A_Left));
			p->timerTiredness = H3_GetTime();

			

			snprintf(p->buffer_ts, 100, "20: 20", 0);

			SH3TextProperties HII =
			{
				.font = p->font,
				.size = 50,
				.fillColor = {255, 0, 0, 255},
				.hasOutline = false,
				.outlineColor = {0,0,0,0},
				.outlineThickness = 0,
				.anchor = A_Center | A_Left,
				.isBold = true,
				.isItalic = false,
				.isUnderlined = false,
				.isViewLocal = false,
			};

			H3_Object_AddComponent(p->texts, TEXTCOMPONENT_CREATE(p->buffer_ts, HII));

		}

		printf("Time : %f\n",H3_GetTime());
		printf("Time in game : %f\n", H3_GetTime() * 10);
		printf("Time tiredness : %f\n", p->timerTiredness);
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
		p->timeLagTiredness = 167 * p->percentTiredness / 100;
		p->hours = (int)H3_GetTime() * 10 / 60;
		p->min = H3_GetTime() * 10 - p->hours * 60;
		printf("\n%d : %d\n", p->hours, p->min);
		H3_Object_SetTranslation(p->fatigueBarOutline, p->cX + 153, p->cY - 180);
		H3_Object_SetTranslation(p->fatigueBarInline, p->cX + p->timeLagTiredness + 153, p->cY - 180);
		H3_Object_SetTranslation(p->texts, p->cX -300, p->cY - 180);
		//printf("Time in game with monstere : %f\n", H3_GetTime() * 10/4);
		printf("percent Tiredness : %f", p->percentTiredness);
	}
