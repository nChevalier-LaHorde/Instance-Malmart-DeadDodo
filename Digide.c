#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include "Inventory.h"
#include <Digide.h>

typedef struct
{
	bool rigthcode;
	bool init;
	H3Handle scene;
	H3Handle digidesprite;
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
	H3Handle nb1;
	H3Handle nb2;
	H3Handle nb3;
	H3Handle nb4;
	int count;
	int nbcode1;
	int nbcode2;
	int nbcode3;
	int nbcode4;
} Digide_Properties;

void* Digide_CreateProperties(H3Handle scene, int nbcode1, int nbcode2, int nbcode3, int nbcode4)
{
	Digide_Properties* properties = malloc(sizeof(Digide_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->init = false;
	properties->init = true;
	properties->scene = scene;
	properties->digidesprite = H3_Object_Create(scene, "digidesprite", NULL);
	properties->btnquit = H3_Object_Create(scene, "btnquit", NULL);
	properties->isbtnquit = false;
	properties->btn1 = H3_Object_Create(scene, "btn1", NULL);
	properties->isbtn1 = false;
	properties->btn2 = H3_Object_Create(scene, "btn2", NULL);
	properties->isbtn2 = false;
	properties->btn3 = H3_Object_Create(scene, "btn3", NULL);
	properties->isbtn3 = false;
	properties->btn4 = H3_Object_Create(scene, "btn4", NULL);
	properties->isbtn4 = false;
	properties->btn5 = H3_Object_Create(scene, "btn5", NULL);
	properties->isbtn5 = false;
	properties->btn6 = H3_Object_Create(scene, "btn6", NULL);
	properties->isbtn6 = false;
	properties->btn7 = H3_Object_Create(scene, "btn7", NULL);
	properties->isbtn7 = false;
	properties->btn8 = H3_Object_Create(scene, "btn8", NULL);
	properties->isbtn8 = false;
	properties->btn9 = H3_Object_Create(scene, "btn9", NULL);
	properties->isbtn9 = false;
	properties->nb1 = H3_Object_Create(scene, "nb1", NULL);
	properties->nb2 = H3_Object_Create(scene, "nb2", NULL);
	properties->nb3 = H3_Object_Create(scene, "nb3", NULL);
	properties->nb4 = H3_Object_Create(scene, "nb4", NULL);
	properties->count = 0;
	properties->nbcode1 = nbcode1;
	properties->nbcode2 = nbcode2;
	properties->nbcode3 = nbcode3;
	properties->nbcode4 = nbcode4;
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
		H3_Object_AddComponent(props->nb1, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb1, 815, 285);
		H3_Object_AddComponent(props->nb2, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb2, 915, 285);
		H3_Object_AddComponent(props->nb3, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb3, 1015, 285);
		H3_Object_AddComponent(props->nb4, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Center | A_Middle));
		H3_Object_Translate(props->nb4, 1115, 285);
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
	printf("%d", props->isbtnquit);
	if (props->isbtnquit) {
		H3_Object_Destroy(object, true);
	}

	if (props->isbtn1) {
		printf("1\n");
	}
	else if (props->isbtn2) {
		printf("2\n");
	}
	else if (props->isbtn3) {
		printf("3\n");
	}
	else if (props->isbtn4) {
		printf("4\n");
	}
	else if (props->isbtn5) {
		printf("5\n");
	}
	else if (props->isbtn6) {
		printf("6\n");
	}
	else if (props->isbtn7) {
		printf("7\n");
	}
	else if (props->isbtn8) {
		printf("8\n");
	}
	else if (props->isbtn9) {
		printf("9\n");
	}

	if (props->count == 4) {
		if (props->nb1 == props->nbcode1 && props->nb2 == props->nbcode2 && props->nb3 == props->nbcode3 && props->nb4 == props->nbcode4) {
			props->rigthcode = true;
			//changer le sprite du digicode avec un truc vert
			//ajouter un son
		}
		else {
			props->count = 0;
			//changer les sprite des 4 nombres avec le sprite nbnull
			//changer le sprite du digicode avec un truc rouge
			//ajouter un son
		}
	}
}