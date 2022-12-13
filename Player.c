#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <components/animatedspritecomponent.h>
#include "Inventory.h"
#include "Weapon.h"
#include <Player.h>

typedef struct
{
	H3Handle cam;
	H3Handle scn;
	float player_x;
	float player_y;
	float speed;
	float run;
	float walk;
	int spotInventory;
	bool init;
	H3Handle objTouch;
	H3Handle kickObj; 
	int playerOnCol;
	int nbrObjTouch;
	float timeKick;
	float w; float h;
	int lastKeyPress;
	bool isBoy;
	bool couldHit;
} Player_Properties;

void* Player_CreateProperties(H3Handle cam, H3Handle scn)
{
	Player_Properties* properties = malloc(sizeof(Player_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->speed = 200;
	properties->run = 250;
	properties->walk = 200;
	properties->cam = cam;
	properties->init = true;
	properties->spotInventory = 2;
	properties->scn = scn;
	properties->lastKeyPress = 0;
	properties->isBoy = true;
	properties->couldHit = false;

	return properties;
}


void Player_Terminate(void* properties)
{
	free(properties);
}

void Player_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {
	Player_Properties* props = (Player_Properties*)properties;
	H3_Transform_GetPosition(H3_Object_GetTransform(object), &props->player_x, &props->player_y);
	if (props->init) {
		props->kickObj = H3_Object_Create2(props->scn, "kickObj", NULL, 3);
		H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(CDT_Dynamic, 24, 22, A_Top, false));
		props->isBoy ? H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/BoyFront.png", A_Center | A_Middle)) : H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/GirlFront.png", A_Center | A_Middle));;
		H3_Object_Translate(object, 960, 540);
		H3_Object_AddComponent(props->kickObj, ANIMATEDSPRITECOMPONENT_CREATE("assets/kick.png", A_Center | A_Middle, 1, 0.1, false));
		//H3_Object_EnablePhysics(props->kickObj, H3_CIRCLE_COLLIDER(2, 10, true));

		H3_Object_AddComponent(object, INVENTORYCOMPONENT_CREATE(object, props->cam));
		H3_Object_SetEnabled(props->kickObj, false);
		
		//------------------------------
		H3_Object_AddComponent(object, WEAPON_CREATE(props->cam, props->scn));
		//----------------------------

		props->init = false;
	}


	//___________________________________________________________________

	H3_Object_SetTranslation(props->cam, props->player_x, props->player_y);
	
	if (H3_Object_HasComponent(object, WEAPON_TYPEID))
	{
		props->couldHit = true;
	}
	//_____________________________________________________________________________


	H3_Object_SetVelocity(object, 0, 0);

	if (H3_Input_IsKeyDown(K_Shift))
	{
		props->speed = props->run;
	}
	else
	{
		props->speed = props->walk;
	}

	if (H3_Input_IsKeyDown(K_D)) {
		props->isBoy ? SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/BoyRight.png", &props->w, &props->h)) : SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/GirlRight.png", &props->w, &props->h));
		H3_Object_AddVelocity(object, props->speed, 0);
		H3_Object_SetTranslation(props->kickObj, props->player_x+30, props->player_y);
		props->lastKeyPress = 0;

		
	}
	if (H3_Input_IsKeyDown(K_Q)) {
		props->isBoy ? SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/BoyLeft.png", &props->w, &props->h)) : SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/GirlLeft.png", &props->w, &props->h));
		H3_Object_AddVelocity(object, -props->speed, 0);
		H3_Object_SetTranslation(props->kickObj, props->player_x-30, props->player_y);
		props->lastKeyPress = 1;
		
	}
	if (H3_Input_IsKeyDown(K_S)) {
		props->isBoy ? SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/BoyFront.png", &props->w, &props->h)) : SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/GirlFront.png", &props->w, &props->h));
		H3_Object_AddVelocity(object, 0, props->speed);
		H3_Object_SetTranslation(props->kickObj, props->player_x, props->player_y+35);
		props->lastKeyPress = 2;
		
	}
	if (H3_Input_IsKeyDown(K_Z)) {
		props->isBoy ? SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/BoyBack.png", &props->w, &props->h)) : SpriteComponent_SetTextureEx(object, H3_Texture_Load("assets/GirlBack.png", &props->w, &props->h));
		H3_Object_AddVelocity(object, 0, -props->speed);
		H3_Object_SetTranslation(props->kickObj, props->player_x, props->player_y-15);
		props->lastKeyPress = 3;
		
		
	}

	if (H3_Input_IsMouseBtnPressed(MB_Left) && props->couldHit)
	{
		H3_Object_SetEnabled(props->kickObj, true);
		if (props->lastKeyPress == 0)
		{
			AnimatedSpriteComponent_SetTextureEx(props->kickObj, H3_Texture_Load("assets/kick.png", &props->w, &props->h));
			AnimatedSpriteComponent_SetFlipXEx(props->kickObj, false);
			AnimatedSpriteComponent_SetFlipYEx(props->kickObj, false);
		

		}
		else if (props->lastKeyPress == 1)
		{
			AnimatedSpriteComponent_SetTextureEx(props->kickObj, H3_Texture_Load("assets/kick.png", &props->w, &props->h));
			AnimatedSpriteComponent_SetFlipXEx(props->kickObj, true);
			AnimatedSpriteComponent_SetFlipYEx(props->kickObj, false);
	
		}
		else if (props->lastKeyPress == 2)
		{
			AnimatedSpriteComponent_SetTextureEx(props->kickObj, H3_Texture_Load("assets/kick2.png", &props->w, &props->h));
			AnimatedSpriteComponent_SetFlipXEx(props->kickObj, false);
			AnimatedSpriteComponent_SetFlipYEx(props->kickObj, true);
			
		}
		else if (props->lastKeyPress == 3)
		{
			AnimatedSpriteComponent_SetTextureEx(props->kickObj, H3_Texture_Load("assets/kick2.png", &props->w, &props->h));
			AnimatedSpriteComponent_SetFlipXEx(props->kickObj, false);
			AnimatedSpriteComponent_SetFlipYEx(props->kickObj, false);
	
		}
		props->timeKick = H3_GetTime();
	}

	if (H3_GetTime() - props->timeKick > 0.1)
	{
		H3_Object_SetEnabled(props->kickObj, false);

		
	}

}

void playerOnCollision(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, PLAYER_TYPEID);
	Player_Properties* pe = (Player_Properties*)(component->properties);
	if (col.other == NULL) {}


	pe->objTouch = col.other;
	pe->playerOnCol = 1;

	pe->nbrObjTouch += 1;

}

void playerOnCollisionLeave(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, PLAYER_TYPEID);
	Player_Properties* pe = (Player_Properties*)(component->properties);


	if (pe->nbrObjTouch < 2)
	{
		pe->objTouch = NULL;
		pe->playerOnCol = 0;
	}

	pe->nbrObjTouch -= 1;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO(Player, float, player_x);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(Player, float, player_y);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(Player, PLAYER_TYPEID, float, player_x);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, float, player_y);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, float, walk);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, float, run);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, int, lastKeyPress);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, bool, isBoy);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, int, spotInventory);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, int, playerOnCol);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, PLAYER_TYPEID, H3Handle, objTouch);