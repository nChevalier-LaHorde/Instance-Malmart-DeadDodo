#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include "Inventory.h"
#include <Digide.h>

/*typedef struct
{
	int* code;
	bool rigthcode;
	bool init;
	H3Handle scene;
	H3Handle digidesprite;
	H3Handle parent;
	float w;
	float h;
	H3Handle btnquit; bool isbtnquit; float btnquitx; float btnquity;
	H3Handle btn[9];
	bool isbtn[9];
	char btnname[5];
	char nbname[5];
	char spritebtn[5];
	char spritenb[5];
	char name[20];
	int btncoor[9][2];
	int try[4];
	H3Handle nb[4];
	int count;

} Digide_Properties;

void* Digide_CreateProperties(H3Handle scene, int code[])
{
	Digide_Properties* properties = malloc(sizeof(Digide_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->init = false;
	properties->init = true;
	properties->scene = scene;
	properties->parent = H3_Object_Create(scene, "parent", NULL);
	properties->digidesprite = H3_Object_Create(scene, "digidesprite", properties->parent);
	properties->btnquit = H3_Object_Create(scene, "btnquit", properties->parent);
	properties->isbtnquit = false;

	for (int i = 1; i < 8; i += 3) {
		properties->btncoor[i][1] = 810;
	}
	for (int i = 2; i < 9; i += 3) {
		properties->btncoor[i][1] = 960;
	}
	for (int i = 3; i < 10; i += 3) {
		properties->btncoor[i][1] = 1110;
	}
	for (int i = 1; i < 4; i ++) {
		properties->btncoor[i][2] = 490;
	}
	for (int i = 4; i < 7; i ++) {
		properties->btncoor[i][2] = 640;
	}
	for (int i = 7; i < 10; i ++) {
		properties->btncoor[i][2] = 790;
	}

	for (int i = 0; i < 9; i++) {
		snprintf(properties->btnname, 5, "btn%d", i);
		properties->btn[i] = H3_Object_Create(scene, properties->btnname, properties->parent);
		properties->isbtn[i] = false;
	}
	for (int i = 0; i < 4; i++) {
		snprintf(properties->nbname, 5, "nb%d", i);
		properties->nb[i] = H3_Object_Create(scene, properties->nbname, properties->parent);
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
		H3_Object_Translate(props->digidesprite, 960, 540);
		H3_Object_AddComponent(props->btnquit, SPRITECOMPONENT_CREATE("assets/btnquit.png", A_Center | A_Middle));
		H3_Object_Translate(props->btnquit, 1750, 50);
		for (int i = 0; i < 9; i++) {
			snprintf(props->spritebtn, 5, "assets/btnup%d.png", i);
			H3_Object_AddComponent(props->btn[i], SPRITECOMPONENT_CREATE(props->spritebtn, A_Center | A_Middle));
			H3_Object_Translate(props->btn[i], props->btncoor[i][1], props->btncoor[i][2]);
		}
		for (int i = 0; i < 4; i++) {
			H3_Object_AddComponent(props->nb[i], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
			H3_Object_Translate(props->nb[i], props->btncoor[i][1], props->btncoor[i][2]);
		}
		props->init = false;

		H3_Transform_GetPosition(H3_Object_GetTransform(props->btnquit), &props->btnquitx, &props->btnquity);
		props->isbtnquit = H3_Button(h3, SpriteComponent_GetTextureEx(props->btnquit), props->btnquitx, props->btnquity, A_Center | A_Middle);
		for (int i = 0; i < 9; i++) {
			props->isbtn[i] = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn[i]), props->btncoor[i][1], props->btncoor[i][2], A_Center | A_Middle);
		}
	}


	if (props->isbtnquit) {
		H3_Object_Destroy(props->parent, true);
		H3_Object_Destroy(object, true);
	}

	for (int i = 0; i < 9; i++) {
		if (props->isbtn[i]) {
			snprintf(props->name, 20, "assets/%d.png", i);
			SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load(props->name, &props->w, &props->h));
			props->code[props->count] = i;
			props->count += 1;
		}
	}


	if (props->count == 4) {
		if (props->try[1] == props->code[1] && props->try[2] == props->code[2] && props->try[3] == props->code[3] && props->try[3] == props->code[4]) {
			props->rigthcode = true;
			//changer le sprite du digicode avec un truc vert
			//ajouter un son
		}
		else {
			props->count = 0;
			for (int i = 0; i < 4; i++) {
				SpriteComponent_SetTextureEx(props->code[i], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			}
			//changer le sprite du digicode avec un truc rouge
			//ajouter un son
		}
	}
}*/



typedef struct
{
	bool rigthcode;
	bool init;
	H3Handle scene;
	H3Handle digidesprite;
	H3Handle parent;
	H3Handle btnquit; bool isbtnquit; float btnquitx; float btnquity;
	H3Handle btn1; bool isbtn1; float btn1x; float btn1y;
	H3Handle btn2; bool isbtn2; float btn2x; float btn2y;
	H3Handle btn3; bool isbtn3; float btn3x; float btn3y;
	H3Handle btn4; bool isbtn4; float btn4x; float btn4y;
	H3Handle btn5; bool isbtn5; float btn5x; float btn5y;
	H3Handle btn6; bool isbtn6; float btn6x; float btn6y;
	H3Handle btn7; bool isbtn7; float btn7x; float btn7y;
	H3Handle btn8; bool isbtn8; float btn8x; float btn8y;
	H3Handle btn9; bool isbtn9; float btn9x; float btn9y;
	int try[4];
	H3Handle nb[4];
	int count;
	int* code;
	char nbname[5];
	float w;
	float h;
} Digide_Properties;

void* Digide_CreateProperties(H3Handle scene, int code[])
{
	Digide_Properties* properties = malloc(sizeof(Digide_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->init = false;
	properties->init = true;
	properties->scene = scene;
	properties->parent = H3_Object_Create(scene, "parent", NULL);
	properties->digidesprite = H3_Object_Create(scene, "digidesprite", properties->parent);
	properties->btnquit = H3_Object_Create(scene, "btnquit", properties->parent);
	properties->isbtnquit = false;
	properties->btn1 = H3_Object_Create(scene, "btn1", properties->parent);
	properties->isbtn1 = false;
	properties->btn2 = H3_Object_Create(scene, "btn2", properties->parent);
	properties->isbtn2 = false;
	properties->btn3 = H3_Object_Create(scene, "btn3", properties->parent);
	properties->isbtn3 = false;
	properties->btn4 = H3_Object_Create(scene, "btn4", properties->parent);
	properties->isbtn4 = false;
	properties->btn5 = H3_Object_Create(scene, "btn5", properties->parent);
	properties->isbtn5 = false;
	properties->btn6 = H3_Object_Create(scene, "btn6", properties->parent);
	properties->isbtn6 = false;
	properties->btn7 = H3_Object_Create(scene, "btn7", properties->parent);
	properties->isbtn7 = false;
	properties->btn8 = H3_Object_Create(scene, "btn8", properties->parent);
	properties->isbtn8 = false;
	properties->btn9 = H3_Object_Create(scene, "btn9", properties->parent);
	properties->isbtn9 = false;
	for (int i = 0; i < 4; i++) {
		snprintf(properties->nbname, 5, "nb%d", i);
		properties->nb[i] = H3_Object_Create(scene, properties->nbname, properties->parent);
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
		H3_Object_Translate(props->digidesprite, 960, 540);
		H3_Object_AddComponent(props->btnquit, SPRITECOMPONENT_CREATE("assets/btnquit.png", A_Center | A_Middle));
		H3_Object_Translate(props->btnquit, 1750, 50);
		H3_Object_AddComponent(props->btn1, SPRITECOMPONENT_CREATE("assets/btnup1.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn1, 810, 490);
		H3_Object_AddComponent(props->btn2, SPRITECOMPONENT_CREATE("assets/btnup2.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn2, 960, 490);
		H3_Object_AddComponent(props->btn3, SPRITECOMPONENT_CREATE("assets/btnup3.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn3, 1110, 490);
		H3_Object_AddComponent(props->btn4, SPRITECOMPONENT_CREATE("assets/btnup4.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn4, 810, 640);
		H3_Object_AddComponent(props->btn5, SPRITECOMPONENT_CREATE("assets/btnup5.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn5, 960, 640);
		H3_Object_AddComponent(props->btn6, SPRITECOMPONENT_CREATE("assets/btnup6.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn6, 1110, 640);
		H3_Object_AddComponent(props->btn7, SPRITECOMPONENT_CREATE("assets/btnup7.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn7, 810, 790);
		H3_Object_AddComponent(props->btn8, SPRITECOMPONENT_CREATE("assets/btnup8.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn8, 960, 790);
		H3_Object_AddComponent(props->btn9, SPRITECOMPONENT_CREATE("assets/btnup9.png", A_Center | A_Middle));
		H3_Object_Translate(props->btn9, 1110, 790);
		H3_Object_AddComponent(props->nb[0], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb[0], 815, 285);
		H3_Object_AddComponent(props->nb[1], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb[1], 915, 285);
		H3_Object_AddComponent(props->nb[2], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb[2], 1015, 285);
		H3_Object_AddComponent(props->nb[3], SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb[3], 1115, 285);
		props->init = false;
	}
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btnquit), &props->btnquitx, &props->btnquity);
	props->isbtnquit = H3_Button(h3, SpriteComponent_GetTextureEx(props->btnquit), props->btnquitx, props->btnquity, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn1), &props->btn1x, &props->btn1y);
	props->isbtn1 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn1), props->btn1x, props->btn1y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn2), &props->btn2x, &props->btn2y);
	props->isbtn2 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn2), props->btn2x, props->btn2y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn3), &props->btn3x, &props->btn3y);
	props->isbtn3 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn3), props->btn3x, props->btn3y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn4), &props->btn4x, &props->btn4y);
	props->isbtn4 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn4), props->btn4x, props->btn4y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn5), &props->btn5x, &props->btn5y);
	props->isbtn5 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn5), props->btn5x, props->btn5y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn6), &props->btn6x, &props->btn6y);
	props->isbtn6 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn6), props->btn6x, props->btn6y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn7), &props->btn7x, &props->btn7y);
	props->isbtn7 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn7), props->btn7x, props->btn7y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn8), &props->btn8x, &props->btn8y);
	props->isbtn8 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn8), props->btn8x, props->btn8y, A_Center | A_Middle);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->btn9), &props->btn9x, &props->btn9y);
	props->isbtn9 = H3_Button(h3, SpriteComponent_GetTextureEx(props->btn9), props->btn9x, props->btn9y, A_Center | A_Middle);

	if (props->isbtnquit) {
		H3_Object_Destroy(props->parent, true);
		H3_Object_Destroy(object, true);
	}

	if (props->isbtn1) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/1.png", &props->w, &props->h));
		props->try[props->count] = 1;
		props->count += 1;
	}
	else if (props->isbtn2) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/2.png", &props->w, &props->h));
		props->try[props->count] = 2;
		props->count += 1;
	}
	else if (props->isbtn3) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/3.png", &props->w, &props->h));
		props->try[props->count] = 3;
		props->count += 1;
	}
	else if (props->isbtn4) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/4.png", &props->w, &props->h));
		props->try[props->count] = 4;
		props->count += 1;
	}
	else if (props->isbtn5) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/5.png", &props->w, &props->h));
		props->try[props->count] = 5;
		props->count += 1;
	}
	else if (props->isbtn6) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/6.png", &props->w, &props->h));
		props->try[props->count] = 6;
		props->count += 1;
	}
	else if (props->isbtn7) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/7.png", &props->w, &props->h));
		props->try[props->count] = 7;
		props->count += 1;
	}
	else if (props->isbtn8) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/8.png", &props->w, &props->h));
		props->try[props->count] = 8;
		props->count += 1;
	}
	else if (props->isbtn9) {
		SpriteComponent_SetTextureEx(props->nb[props->count], H3_Texture_Load("assets/9.png", &props->w, &props->h));
		props->try[props->count] = 9;
		props->count += 1;
	}

	if (props->count == 4) {
		if (props->try[0] == props->code[0] && props->try[1] == props->code[1] && props->try[2] == props->code[2] && props->try[3] == props->code[3]) {
			props->rigthcode = true;
			H3_Object_Destroy(props->parent, true);
			H3_Object_Destroy(object, true);
			//changer le sprite du digicode avec un truc vert
			//ajouter un son
		}
		else {
			props->count = 0;
			SpriteComponent_SetTextureEx(props->nb[0], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			SpriteComponent_SetTextureEx(props->nb[1], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			SpriteComponent_SetTextureEx(props->nb[2], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			SpriteComponent_SetTextureEx(props->nb[3], H3_Texture_Load("assets/nbnull.png", &props->w, &props->h));
			//changer le sprite du digicode avec un truc rouge
			//ajouter un son
		}
	}
}