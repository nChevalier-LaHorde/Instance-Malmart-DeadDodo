#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include "Digide.h"


typedef struct
{
	bool rigthcode;
	bool init;
	H3Handle scene;
	H3Handle player;
	H3Handle digidesprite;
	H3Handle parent;
	H3Handle btnquit; float btnquitx; float btnquity;
	H3Handle btn1; float btn1x; float btn1y;
	H3Handle btn2; float btn2x; float btn2y;
	H3Handle btn3; float btn3x; float btn3y;
	H3Handle btn4; float btn4x; float btn4y;
	H3Handle btn5; float btn5x; float btn5y;
	H3Handle btn6; float btn6x; float btn6y;
	H3Handle btn7; float btn7x; float btn7y;
	H3Handle btn8; float btn8x; float btn8y;
	H3Handle btn9; float btn9x; float btn9y;
	int try[4];
	H3Handle nb[4];
	int count;
	int* code;
	char nbname[5];
	float playerx;
	float playery;
	float w;
	float h;
	float digitex;
	float digitey;
	int mousex;
	int mousey;
} Digide_Properties;


void* Digide_CreateProperties(H3Handle scene, int code[], H3Handle player)
{
	Digide_Properties* properties = malloc(sizeof(Digide_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->player = player;
	properties->init = true;
	properties->scene = scene;
	properties->digitex = 400;
	properties->digitex = 500;
	properties->parent = H3_Object_Create(scene, "parent", NULL);
	properties->digidesprite = H3_Object_Create2(scene, "digidesprite", properties->parent, 10);
	properties->btnquit = H3_Object_Create2(scene, "btnquit", properties->parent, 10);
	properties->btn1 = H3_Object_Create2(scene, "btn1", properties->parent, 10);
	properties->btn2 = H3_Object_Create2(scene, "btn2", properties->parent, 10);
	properties->btn3 = H3_Object_Create2(scene, "btn3", properties->parent, 10);
	properties->btn4 = H3_Object_Create2(scene, "btn4", properties->parent, 10);
	properties->btn5 = H3_Object_Create2(scene, "btn5", properties->parent, 10);
	properties->btn6 = H3_Object_Create2(scene, "btn6", properties->parent, 10);
	properties->btn7 = H3_Object_Create2(scene, "btn7", properties->parent, 10);
	properties->btn8 = H3_Object_Create2(scene, "btn8", properties->parent, 10);
	properties->btn9 = H3_Object_Create2(scene, "btn9", properties->parent, 10);
	for (int i = 0; i < 4; i++) {
		snprintf(properties->nbname, 5, "nb%d", i);
		properties->nb[i] = H3_Object_Create2(scene, properties->nbname, properties->parent,11);
	}
	properties->count = 0;
	properties->code = code;
	return properties;
}


void Digide_Terminate(void* properties)
{
	free(properties);
}


void Digide_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {
	Digide_Properties* props = (Digide_Properties*)properties;

	if (props->init) {
		H3_Object_AddComponent(props->digidesprite, SPRITECOMPONENT_CREATE("assets/digide.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btnquit, SPRITECOMPONENT_CREATE("assets/btnquit.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn1, SPRITECOMPONENT_CREATE("assets/btnup1.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn2, SPRITECOMPONENT_CREATE("assets/btnup2.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn3, SPRITECOMPONENT_CREATE("assets/btnup3.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn4, SPRITECOMPONENT_CREATE("assets/btnup4.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn5, SPRITECOMPONENT_CREATE("assets/btnup5.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn6, SPRITECOMPONENT_CREATE("assets/btnup6.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn7, SPRITECOMPONENT_CREATE("assets/btnup7.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn8, SPRITECOMPONENT_CREATE("assets/btnup8.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->btn9, SPRITECOMPONENT_CREATE("assets/btnup9.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->nb[0], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->nb[1], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->nb[2], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_AddComponent(props->nb[3], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		props->init = false;
	}
	H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &props->playerx, &props->playery);
	H3_Object_SetTranslation(props->digidesprite, props->playerx, props->playery);
	H3_Object_SetTranslation(props->btnquit, props->playerx + 110, props->playery - 150);
	H3_Object_SetTranslation(props->btn1, props->playerx - 49, props->playery - 10);
	H3_Object_SetTranslation(props->btn2, props->playerx, props->playery - 10);
	H3_Object_SetTranslation(props->btn3, props->playerx + 49, props->playery - 10);
	H3_Object_SetTranslation(props->btn4, props->playerx - 49, props->playery + 39);
	H3_Object_SetTranslation(props->btn5, props->playerx, props->playery + 39);
	H3_Object_SetTranslation(props->btn6, props->playerx + 49, props->playery + 39);
	H3_Object_SetTranslation(props->btn7, props->playerx - 49, props->playery + 88);
	H3_Object_SetTranslation(props->btn8, props->playerx, props->playery + 88);
	H3_Object_SetTranslation(props->btn9, props->playerx + 49, props->playery + 88);
	H3_Object_SetTranslation(props->nb[0], props->playerx - 45, props->playery - 86);
	H3_Object_SetTranslation(props->nb[1], props->playerx - 15, props->playery - 86);
	H3_Object_SetTranslation(props->nb[2], props->playerx + 15, props->playery - 86);
	H3_Object_SetTranslation(props->nb[3], props->playerx + 45, props->playery - 86);

	
	H3_Input_GetMousePos(h3, &props->mousex, &props->mousey);
	
	if (H3_Input_IsMouseBtnPressed(MB_Left)) {

		if (props->mousex < 960 + 118 && props->mousex > 960 + 102 && props->mousey < 540 - 142 && props->mousey > 540 - 158) {
			H3_Object_Destroy(props->parent, true);
			H3_Object_Destroy(object, true);
		}

		else if (props->mousex < 960 - 25 && props->mousex > 960 - 75 && props->mousey < 540 + 15 && props->mousey > 540 - 35) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/1.png", &props->w, &props->h));
			props->try[props->count] = 1;
			props->count += 1;
		}
		else if (props->mousex < 960 + 25 && props->mousex > 960 - 25 && props->mousey < 540 + 15 && props->mousey > 540 - 35) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/2.png", &props->w, &props->h));
			props->try[props->count] = 2;
			props->count += 1;
		}
		else if (props->mousex < 960 + 75 && props->mousex > 960 + 25 && props->mousey < 540 + 15 && props->mousey > 540 - 35) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/3.png", &props->w, &props->h));
			props->try[props->count] = 3;
			props->count += 1;
		}
		else if (props->mousex < 960 - 25 && props->mousex > 960 - 75 && props->mousey < 540 + 65 && props->mousey > 540 + 15) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/4.png", &props->w, &props->h));
			props->try[props->count] = 4;
			props->count += 1;
		}
		else if (props->mousex < 960 + 25 && props->mousex > 960 - 25 && props->mousey < 540 + 65 && props->mousey > 540 + 15) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/5.png", &props->w, &props->h));
			props->try[props->count] = 5;
			props->count += 1;
		}
		else if (props->mousex < 960 + 75 && props->mousex > 960 + 25 && props->mousey < 540 + 65 && props->mousey > 540 + 15) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/6.png", &props->w, &props->h));
			props->try[props->count] = 6;
			props->count += 1;
		}
		else if (props->mousex < 960 - 25 && props->mousex > 960 - 75 && props->mousey < 540 + 115 && props->mousey > 540 + 65) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/7.png", &props->w, &props->h));
			props->try[props->count] = 7;
			props->count += 1;
		}
		else if (props->mousex < 960 + 25 && props->mousex > 960 - 25 && props->mousey < 540 + 115 && props->mousey > 540 + 65) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/8.png", &props->w, &props->h));
			props->try[props->count] = 8;
			props->count += 1;
		}
		else if (props->mousex < 960 + 75 && props->mousex > 960 + 25 && props->mousey < 540 + 115 && props->mousey > 540 + 65) {
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/9.png", &props->w, &props->h));
			props->try[props->count] = 9;
			props->count += 1;
		}
	}

	if (props->count == 4) {
		if (props->try[0] == props->code[0] && props->try[1] == props->code[1] && props->try[2] == props->code[2] && props->try[3] == props->code[3]) {
			props->rigthcode = true;
			H3_Object_Destroy(props->parent, true);
			H3_Object_Destroy(object, true);
		}
		else {
			props->count = 0;
			SpriteComponent_SetTextureEx(props->nb[0], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			SpriteComponent_SetTextureEx(props->nb[1], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			SpriteComponent_SetTextureEx(props->nb[2], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			SpriteComponent_SetTextureEx(props->nb[3], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
		}
	}
}