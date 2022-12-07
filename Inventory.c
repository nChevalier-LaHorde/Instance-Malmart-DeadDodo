#include "Inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include<components/spritecomponent.h>
#include <components/cameracomponent.h>
#include <components/textcomponent.h>
#include "player.h"
typedef struct
{
	float px; float py;
	int recup;
	H3Handle objRecup;
	H3Handle player;
	H3Handle stock1;
	H3Handle stock2;

} InventoryComponent_Properties;




void InventoryComponent_Terminate(void* properties)
{

	free(properties);
}



void* InventoryComponent_CreateProperties(H3Handle player)
{
	InventoryComponent_Properties* properties = malloc(sizeof(InventoryComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");


	properties->stock1 = NULL;
	properties->stock2 = NULL;
	properties->recup = 0;
	properties->player = player;


	return properties;
}


void UpInventory(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{

	InventoryComponent_Properties* p = (InventoryComponent_Properties*)properties;
	p->recup = PlayerComponent_GetplayerOnCollisionEx(p->player);
	printf("recup = %d\n", p->recup);
	if (p->recup == 1)
	{
		if (H3_Input_IsKeyPressed(K_A))
		{
			if (p->stock1 == NULL && p->objRecup != NULL)
			{
				p->objRecup = PlayerComponent_GetobjTouchEx(p->player);
				p->stock1 = p->objRecup;
				H3_Object_SetTranslation(p->stock1, -100, -100);
				/*H3_Object_SetEnabled(p->objRecup, false);*/
			}
			else if (p->stock2 == NULL && p->objRecup != NULL)
			{
				p->objRecup = PlayerComponent_GetobjTouchEx(p->player);
				p->stock2 = p->objRecup;
				H3_Object_SetTranslation(p->stock2, -100, -100);
			}



		}
	}
	else if (p->recup == 0 && p->stock1 != NULL)
	{
		if (H3_Input_IsKeyPressed(K_A))
		{
			if (p->stock2 != NULL)
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

}


