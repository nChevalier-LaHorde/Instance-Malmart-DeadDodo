#include "Inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <components/spritecomponent.h>
#include <components/cameracomponent.h>
#include <components/textcomponent.h>
#include "Player.h"
#include "Clue.h"
#include "TypeCanTake.h"

typedef struct
{
	bool init;
	H3Handle scn;

	float px; float py;
	int selected;
	int recup;
	H3Handle objRecup;
	H3Handle player;
	H3Handle stock1;
	H3Handle stock2;
	H3Handle stock3;

	H3Handle invHud1;
	H3Handle invHud2;
	H3Handle invHud3;
	H3Handle invHudSelected1;
	H3Handle invHudSelected2;
	H3Handle invHudSelected3;
	H3Handle stockSelected;

	H3Handle cam;
	float camX;
	float camY;
	bool itSWeapon;

} InventoryComponent_Properties;




void InventoryComponent_Terminate(void* properties)
{

	free(properties);
}



void* InventoryComponent_CreateProperties(H3Handle player, H3Handle cam, H3Handle scn)
{
	InventoryComponent_Properties* properties = malloc(sizeof(InventoryComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scn = scn;
	properties->stock1 = NULL;
	properties->stock2 = NULL;
	properties->stock3 = NULL;
	properties->recup = 0;
	properties->player = player;
	properties->cam = cam;
	properties->init = true;
	properties->itSWeapon = false;
	properties->stockSelected = NULL;


	return properties;
}


void UpInventory(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

	InventoryComponent_Properties* p = (InventoryComponent_Properties*)properties;

	p->recup = Player_GetplayerOnColEx(p->player);
	H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->camX, &p->camY);


	if (p->init) {
		p->invHud1 = H3_Object_Create2(p->scn, "invHud1", NULL, 7);
		p->invHud2 = H3_Object_Create2(p->scn, "invHud2", NULL, 7);

		p->invHudSelected1 = H3_Object_Create2(p->scn, "invHudSelected1", NULL, 7);
		p->invHudSelected2 = H3_Object_Create2(p->scn, "invHudSelected2", NULL, 7);



		H3_Object_AddComponent(p->invHud1, SPRITECOMPONENT_CREATE("assets/Inventory/HUD_not_selected.png", A_Center | A_Middle));
		H3_Object_AddComponent(p->invHud2, SPRITECOMPONENT_CREATE("assets/Inventory/HUD_not_selected.png", A_Center | A_Middle));

		H3_Object_AddComponent(p->invHudSelected1, SPRITECOMPONENT_CREATE("assets/Inventory/HUD_selected.png", A_Center | A_Middle));
		H3_Object_AddComponent(p->invHudSelected2, SPRITECOMPONENT_CREATE("assets/Inventory/HUD_selected.png", A_Center | A_Middle));


		H3_Object_SetEnabled(p->invHud1, false);
		H3_Object_SetEnabled(p->invHud2, false);
		H3_Object_SetEnabled(p->invHudSelected1, true);
		H3_Object_SetEnabled(p->invHudSelected2, true);

		if (Player_GetspotInventoryEx(object) == 3)
		{
			p->invHud3 = H3_Object_Create2(p->scn, "invHud3", NULL, 7);
			p->invHudSelected3 = H3_Object_Create2(p->scn, "invHudSelected3", NULL, 7);
			H3_Object_AddComponent(p->invHud3, SPRITECOMPONENT_CREATE("assets/Inventory/HUD_not_selected.png", A_Center | A_Middle));
			H3_Object_AddComponent(p->invHudSelected3, SPRITECOMPONENT_CREATE("assets/Inventory/HUD_selected.png", A_Center | A_Middle));
		}


		p->selected = 1;
		p->init = false;
	}

	H3_Object_SetTranslation(p->invHud1, p->camX + 280, p->camY + 120);
	H3_Object_SetTranslation(p->invHud2, p->camX + 230, p->camY + 120);
	H3_Object_SetTranslation(p->invHudSelected1, p->camX + 280, p->camY + 120);
	H3_Object_SetTranslation(p->invHudSelected2, p->camX + 230, p->camY + 120);
	if (Player_GetspotInventoryEx(object) == 3)
	{
		H3_Object_SetTranslation(p->invHud3, p->camX + 180, p->camY + 120);
		H3_Object_SetTranslation(p->invHudSelected3, p->camX + 180, p->camY + 120);
	}


	if (p->recup == 1)
	{

		if (H3_Input_IsKeyPressed(K_Space))
		{
			if (H3_Object_HasComponent(Player_GetobjTouchEx(p->player), CLUECOMPONENT_TYPEID))
			{
				ClueComponent_SetdisplayEx(Player_GetobjTouchEx(p->player), 1);
			}
			else if (H3_Object_HasComponent(Player_GetobjTouchEx(p->player), TYPECANTAKE_TYPEID))
			{
				if (p->stock1 == NULL && p->objRecup != NULL)
				{

					p->objRecup = Player_GetobjTouchEx(p->player);
					H3_Object_SetRenderOrder(p->objRecup, 8);
					p->stock1 = p->objRecup;
				}
				else if (p->stock2 == NULL && p->objRecup != NULL)
				{

					p->objRecup = Player_GetobjTouchEx(p->player);
					H3_Object_SetRenderOrder(p->objRecup, 8);
					p->stock2 = p->objRecup;

				}
				else if (p->stock3 == NULL && p->objRecup != NULL && Player_GetspotInventoryEx(object) == 3)
				{
					p->objRecup = Player_GetobjTouchEx(p->player);
					H3_Object_SetRenderOrder(p->objRecup, 8);
					p->stock3 = p->objRecup;
				}
			}
		}
	}
	else if (p->recup == 0 )
	{
		if (H3_Input_IsKeyPressed(K_Space))
		{
			if (p->stock3 != NULL && Player_GetspotInventoryEx(object) == 3 && p->selected == 3)
			{
				H3_Object_SetRenderOrder(p->stock3, 3);
				H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
				H3_Object_SetTranslation(p->stock3, p->px, p->py);
				p->stock3 = NULL;

			}
			else if (p->stock2 != NULL && p->selected == 2)
			{
				H3_Object_SetRenderOrder(p->stock2, 3);
				H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
				H3_Object_SetTranslation(p->stock2, p->px, p->py);
				p->stock2 = NULL;
			}
			else if (p->stock1 != NULL && p->selected == 1)
			{
				H3_Object_SetRenderOrder(p->stock1, 3);
				H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
				H3_Object_SetTranslation(p->stock1, p->px, p->py);
				p->stock1 = NULL;
			}

		}
	}

	
	if (p->stock1 != NULL)
	{
		H3_Object_SetTranslation(p->stock1, p->camX + 280, p->camY + 120);
	}
	if (p->stock2 != NULL)
	{
		H3_Object_SetTranslation(p->stock2, p->camX + 230, p->camY + 120);
	}
	if (p->stock3 != NULL)
	{
		H3_Object_SetTranslation(p->stock3, p->camX + 180, p->camY + 120);
	}



	if (H3_Input_IsKeyPressed(K_Left))
	{
		p->selected++;
	}
	else if (H3_Input_IsKeyPressed(K_Right))
	{
		p->selected--;
	}

	switch (p->selected)
	{
	case 0:
		if (Player_GetspotInventoryEx(object) == 3)
		{
			p->selected = 3;
		}
		else
		{
			p->selected = 2;
		}
		break;

	case 1:
		
		H3_Object_SetEnabled(p->invHud1, false);
		H3_Object_SetEnabled(p->invHud2, true);
		H3_Object_SetEnabled(p->invHudSelected1, true);
		H3_Object_SetEnabled(p->invHudSelected2, false);
		p->stockSelected = p->stock1;
		if (Player_GetspotInventoryEx(object) == 3)
		{
			H3_Object_SetEnabled(p->invHud3, true);
			H3_Object_SetEnabled(p->invHudSelected3, false);
		}
		break;

	case 2:
		
		H3_Object_SetEnabled(p->invHud1, true);
		H3_Object_SetEnabled(p->invHud2, false);
		H3_Object_SetEnabled(p->invHudSelected1, false);
		H3_Object_SetEnabled(p->invHudSelected2, true);
		p->stockSelected = p->stock2;
		if (Player_GetspotInventoryEx(object) == 3)
		{
			H3_Object_SetEnabled(p->invHud3, true);
			H3_Object_SetEnabled(p->invHudSelected3, false);
		}

		break;

	case 3:
		if (Player_GetspotInventoryEx(object) == 3)
		{
			
			H3_Object_SetEnabled(p->invHud1, true);
			H3_Object_SetEnabled(p->invHud2, true);
			H3_Object_SetEnabled(p->invHud3, false);
			H3_Object_SetEnabled(p->invHudSelected1, false);
			H3_Object_SetEnabled(p->invHudSelected2, false);
			H3_Object_SetEnabled(p->invHudSelected3, true);
			p->stockSelected = p->stock3;
		}
		else
		{
			p->selected = 1;
		}
		break;

	case 4:
		p->selected = 1;
		break;
	}
}



H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, H3Handle, stockSelected);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, H3Handle, stock1);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, H3Handle, stock2);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, H3Handle, stock3);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, int, selected);