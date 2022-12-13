#include "Inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <components/spritecomponent.h>
#include <components/cameracomponent.h>
#include <components/textcomponent.h>
#include "player.h"
#include "Clue.h"
typedef struct
{
	float px; float py;
	int recup;
	H3Handle objRecup;
	H3Handle player;
	H3Handle stock1;
	H3Handle stock2;
	H3Handle stock3;

	H3Handle cam;
	float camX;
	float camY;

} InventoryComponent_Properties;




void InventoryComponent_Terminate(void* properties)
{

	free(properties);
}



void* InventoryComponent_CreateProperties(H3Handle player, H3Handle cam)
{
	InventoryComponent_Properties* properties = malloc(sizeof(InventoryComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");


	properties->stock1 = NULL;
	properties->stock2 = NULL;
	properties->stock3 = NULL;
	properties->recup = 0;
	properties->player = player;
	properties->cam = cam;


	return properties;
}


void UpInventory(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

	InventoryComponent_Properties* p = (InventoryComponent_Properties*)properties;

	p->recup = Player_GetplayerOnColEx(p->player);
	H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->camX, &p->camY);

	if (p->recup == 1)
	{
	
		if (H3_Input_IsKeyPressed(K_Space) )
		{
			if (H3_Object_HasComponent(Player_GetobjTouchEx(p->player), CLUECOMPONENT_TYPEID))
			{
				ClueComponent_SetdisplayEx(Player_GetobjTouchEx(p->player), 1);
			}
			else if (p->stock1 == NULL && p->objRecup != NULL)
			{
				p->objRecup = Player_GetobjTouchEx(p->player);
				p->stock1 = p->objRecup;
			}
			else if (p->stock2 == NULL && p->objRecup != NULL)
			{
				p->objRecup = Player_GetobjTouchEx(p->player);
				p->stock2 = p->objRecup;
				
			}
			else if (p->stock3 == NULL && p->objRecup != NULL && Player_GetspotInventoryEx(object) == 3)
			{
				p->objRecup = Player_GetobjTouchEx(p->player);
				p->stock3 = p->objRecup;
				//H3_Object_SetTranslation(p->stock3, -p->camX / (1920 / 2), -p->camY / (1080 / 2));
			}



		}
	}
	else if (p->recup == 0 && p->stock1 != NULL)
	{
		if (H3_Input_IsKeyPressed(K_Space))
		{
			if (p->stock3 != NULL  && Player_GetspotInventoryEx(object) == 3)
			{
				H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
				H3_Object_SetTranslation(p->stock3, p->px, p->py);
				p->stock3 = NULL;

			}
			else if (p->stock2 != NULL)
			{
				H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
				H3_Object_SetTranslation(p->stock2, p->px, p->py);
				p->stock2 = NULL;
			}
			else if (p->stock1 != NULL)
			{
				H3_Transform_GetPosition(H3_Object_GetTransform(object), &p->px, &p->py);
				H3_Object_SetTranslation(p->stock1, p->px, p->py);
				p->stock1 = NULL;
			}

		}
	}

	/*printf("%d \n", p->recup);*/

	// move inventory
	if (p->stock1 != NULL) 
	{
		H3_Object_SetTranslation(p->stock1, p->camX + 280, p->camY - 50);
	}
	if (p->stock2 != NULL)
	{
		H3_Object_SetTranslation(p->stock2, p->camX + 280, p->camY + 25);
	}
	if (p->stock3 != NULL)
	{
		H3_Object_SetTranslation(p->stock3, p->camX + 280, p->camY + 100);
	}



	if (H3_Input_IsKeyPressed(K_Q))
	{

	}
	else if (H3_Input_IsKeyPressed(K_D))
	{
		
	}

}