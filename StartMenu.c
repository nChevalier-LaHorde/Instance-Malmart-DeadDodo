#include "StartMenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<components/spritecomponent.h>
#include <components/maplayercomponent.h>
#include <components/cameracomponent.h>

typedef struct
{
	int init;
	H3Handle btnStart; bool stateBtnStart; float x_BtnStart; float y_BtnStart;
	H3Handle btnPlayerChoose; bool stateBtnPlayerChoose; H3Handle btnExit; bool stateBtnExit;
	H3Handle h3; H3Handle scn; H3Handle nameOfGame; H3Handle map; H3Handle obj_map1; H3Handle obj_map2; H3Handle obj_map3; H3Handle obj_map4; H3Handle blurring;// floutage
	H3Handle cam; float cx; float cy; float vcx; float vcy; float slewRate;/*Vittesse de blayage de la map sur le menu de démarage*/
} SMComponent_Properties;




void SMComponent_Terminate(void* properties)
{

	free(properties);
}



void* SMComponent_CreateProperties(H3Handle h3, H3Handle scn)
{
	SMComponent_Properties* properties = malloc(sizeof(SMComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = 0;
	properties->h3 = h3;
	properties->scn = scn;
	//cam
	properties->cam = H3_Object_Create(properties->scn, "cam", NULL);
	//btn Start
	properties->btnStart = H3_Object_Create2(properties->scn, "btnStart", NULL,5);
	properties->stateBtnStart = false;
	properties->x_BtnStart = 960;
	properties->y_BtnStart = 540;
	// btn Player choose
	properties->btnPlayerChoose = H3_Object_Create2(properties->scn, "btnPlayerChoose", NULL, 5);
	properties->stateBtnPlayerChoose = false;
	// btn Exit
	properties->btnExit = H3_Object_Create2(properties->scn, "btnExit", NULL, 5);
	properties->stateBtnExit = false;

	// Other
	properties->nameOfGame = H3_Object_Create2(properties->scn, "nameOfGame", NULL,5);
	properties->map = H3_Map_Load("assets/MapMagasin.tmx");
	properties->obj_map1 = H3_Object_Create2(properties->scn, "obj_map1", NULL,0);
	properties->obj_map2 = H3_Object_Create2(properties->scn, "obj_map2", NULL,1);
	properties->obj_map3 = H3_Object_Create2(properties->scn, "obj_map3", NULL,2);
	properties->obj_map4 = H3_Object_Create2(properties->scn, "obj_map4", NULL,4);
	properties->blurring = H3_Object_Create2(properties->scn, "blurring", properties->cam, 1);
	properties->slewRate = 100;
	

	return properties;
}

void UpSM(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	SMComponent_Properties* p = (SMComponent_Properties*)properties;
	if (p->init == 0)
	{
		p->init = 1;
		H3_Object_AddComponent(p->cam, CAMERACOMPONENT_CREATE(1920, 1080));
		H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->cx, &p->cy);
		H3_Object_SetTranslation(p->cam, 400.0f, 400.0f);
		H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->cx, &p->cy);
		H3_Object_AddComponent(p->btnStart, SPRITECOMPONENT_CREATE("assets/BtnStart.png", A_Center + A_Middle));
		H3_Object_AddComponent(p->btnPlayerChoose, SPRITECOMPONENT_CREATE("assets/Btn_Chara.png", A_Center + A_Middle));
		H3_Object_AddComponent(p->btnExit, SPRITECOMPONENT_CREATE("assets/Btn_Exit.png", A_Center + A_Middle));
		H3_Object_AddComponent(p->nameOfGame, SPRITECOMPONENT_CREATE("assets/NomDu Jeu.png", A_Center + A_Middle));
		H3_Object_AddComponent(p->blurring, SPRITECOMPONENT_CREATE("assets/floutage_menu.png", A_Center + A_Middle));
		H3_Object_EnablePhysics(p->cam, H3_BOX_COLLIDER(2, 50, 50, A_Top | A_Middle, true));
		

		H3_Object_AddComponent(p->obj_map1, MAPLAYERCOMPONENT_CREATE(p->map, "map"));
		H3_Object_AddComponent(p->obj_map2, MAPLAYERCOMPONENT_CREATE(p->map, "interiorLayer"));
		H3_Object_AddComponent(p->obj_map3, MAPLAYERCOMPONENT_CREATE(p->map, "interiorLayer2"));
		H3_Object_AddComponent(p->obj_map4, MAPLAYERCOMPONENT_CREATE(p->map, "interiorLayer3"));
		
		H3_Object_SetVelocity(p->cam, 100, 100);

	}
	H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->cx, &p->cy);
	H3_Object_SetTranslation(p->nameOfGame, p->cx, p->cy-350);
	H3_Object_SetTranslation(p->btnStart, p->cx, p->cy-50);
	H3_Object_SetTranslation(p->btnPlayerChoose, p->cx, p->cy+250);
	H3_Object_SetTranslation(p->btnExit, p->cx+850, p->cy + 400);

	//printf("CAM : %f /// %f\n", p->cx, p->cy);
	//printf("BTN : %f /// %f\n", p->x_BtnStart, p->y_BtnStart);
	p->stateBtnStart = H3_Button(h3, SpriteComponent_GetTextureEx(p->btnStart), p->x_BtnStart, p->y_BtnStart-50, A_Center + A_Middle);
	p->stateBtnPlayerChoose = H3_Button(h3, SpriteComponent_GetTextureEx(p->btnPlayerChoose), p->x_BtnStart, p->y_BtnStart+250, A_Center + A_Middle);
	p->stateBtnExit = H3_Button(h3, SpriteComponent_GetTextureEx(p->btnExit), p->x_BtnStart+850, p->y_BtnStart + 400, A_Center + A_Middle);

	H3_Object_GetVelocity(p->cam, &p->vcx, &p->vcy);
	if (p->cx < 0)
	{
		H3_Object_SetVelocity(p->cam, p->slewRate, p->vcy);
	}
	if (p->cx > 2000)
	{
		H3_Object_SetVelocity(p->cam, -p->slewRate, p->vcy);
	}
	if (p->cy < 0)
	{
		H3_Object_SetVelocity(p->cam, p->vcy, p->slewRate);
	}
	if (p->cy > 1200)
	{
		H3_Object_SetVelocity(p->cam, p->vcy, -p->slewRate);
	}

	
	if (p->stateBtnStart)
	{
		printf("a!");
	}
	if (p->stateBtnPlayerChoose)
	{
		printf("BB");
	}
	if (p->stateBtnExit)
	{
		printf("EXIT");
	}

}


H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(SMComponent, SMCOMPONENT_TYPEID, bool, stateBtnStart);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(SMComponent, SMCOMPONENT_TYPEID, bool, stateBtnPlayerChoose);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(SMComponent, SMCOMPONENT_TYPEID, bool, stateBtnExit);

