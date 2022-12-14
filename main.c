#include <h3.h>
#include <stdio.h>
#include <time.h>
#include <components/cameracomponent.h>
#include <Player.h>
#include <Digide.h>
#include <math.h>
#include <components/spritecomponent.h>
#include <components/maplayercomponent.h>
#include <components/textcomponent.h>
#include "StartMenu.h"
#include "Object.h"
#include <stdlib.h>
#include <bootMenu.h>
#include <credit.h>
#include <chooseCharacter.h>
#include "Clue.h"


#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG


int main(int argc, char** argv)
{

	srand(time(NULL));
	int screen_x = 1920;
	int screen_y = 1080;
	int nbcode1 = rand() % 9 + 1;
	int nbcode2 = rand() % 9 + 1;
	int nbcode3 = rand() % 9 + 1;
	int nbcode4 = rand() % 9 + 1;

	H3Handle h3 = H3_Init((SH3InitParams) {
		.width = screen_x,
			.height = screen_y,
			.fullscreen = false,
			.windowTitle = "Magazin",
	});

	int width = 100;
	int height = 100;
	bool scnTurn = true;
	bool exitGame = true;
	int iWantThis = 0; //Parameter to know which scene should be used

	H3Handle scnFirstLunch = H3_Scene_Create(h3, true);
	H3Handle scnMenu = H3_Scene_Create(h3, true);
	H3Handle scnMenuChoose = H3_Scene_Create(h3, true);
	H3Handle scn = H3_Scene_Create(h3, true);

	int dontBtnMenu = 0;

	////////////////////////////
	int stateMenu = 0;

	//create map 
	H3Handle map = H3_Map_Load("assets/MapMagasin.tmx");
	H3_Map_RegisterObjectLayerForPhysicsInScene(scn, map, "collider");

	H3Handle mapLayer = H3_Object_Create(scn, "map1", NULL);
	H3_Object_AddComponent(mapLayer, MAPLAYERCOMPONENT_CREATE(map, "map"));
	H3_Object_SetRenderOrder(mapLayer, 0);

	H3Handle mapLayer1 = H3_Object_Create(scn, "map2", NULL);
	H3_Object_AddComponent(mapLayer1, MAPLAYERCOMPONENT_CREATE(map, "interiorLayer"));
	H3_Object_SetRenderOrder(mapLayer1, 1);

	H3Handle mapLayer2 = H3_Object_Create(scn, "map3", NULL);
	H3_Object_AddComponent(mapLayer2, MAPLAYERCOMPONENT_CREATE(map, "interiorLayer2"));
	H3_Object_SetRenderOrder(mapLayer2, 2);

	H3Handle mapLayer3 = H3_Object_Create(scn, "map4", NULL);
	H3_Object_AddComponent(mapLayer3, MAPLAYERCOMPONENT_CREATE(map, "interiorLayer3"));
	H3_Object_SetRenderOrder(mapLayer3, 4);

	H3Handle camera = H3_Object_Create(scn, "camera", NULL);
	H3_Object_AddComponent(camera, CAMERACOMPONENT_CREATE(screen_x / 3, screen_y / 3));

	H3Handle gameObject = H3_Object_Create(scn, "second_obj", NULL);
	H3_Object_AddComponent(gameObject, OBJECTCOMPONENT_CREATE(scn, h3, camera, &iWantThis));

	H3Handle player = H3_Object_Create2(scn, "player", NULL, 3);
	H3_Object_AddComponent(player, PLAYER_CREATE(camera, scn, gameObject));

	bool stateWindow = true;

	//// boot
	H3Handle boot = H3_Object_Create(scnFirstLunch, "boot", NULL);
	H3_Object_AddComponent(boot, BOOTMENUCOMPONENT_CREATE(scnFirstLunch, stateMenu));

	//// credit
	H3Handle credit = H3_Object_Create(scnFirstLunch, "credit", NULL);

	////  menu character
	H3Handle selectCharacter = H3_Object_Create(scnMenuChoose, "selectCharacter", NULL);
	H3_Object_AddComponent(selectCharacter, CHARACTERCOMPONENT_CREATE(scnMenuChoose, player));

	H3Handle selectCharacterCamera = H3_Object_Create(scnMenuChoose, "selectCharacterCamera", NULL);
	H3_Object_AddComponent(selectCharacterCamera, CAMERACOMPONENT_CREATE(screen_x, screen_y));


	H3Handle first_obj = H3_Object_Create(scnMenu, "first_obj", NULL);
	H3_Object_AddComponent(first_obj, SMCOMPONENT_CREATE(h3, scnMenu)); // ajoute le Main Menu a first object

	


	////////OBJECT TEST/////////////////
	H3Handle obj1 = H3_Object_Create(scn, "obj1", NULL);
	H3Handle obj2 = H3_Object_Create(scn, "obj2", NULL);
	H3Handle obj3 = H3_Object_Create(scn, "obj3", NULL);
	H3Handle obj4 = H3_Object_Create(scn, "obj4", NULL);

	H3_Object_AddComponent(obj1, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Middle + A_Center));
	H3_Object_AddComponent(obj2, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Middle + A_Center));
	H3_Object_AddComponent(obj3, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Middle + A_Center));
	H3_Object_AddComponent(obj4, SPRITECOMPONENT_CREATE("assets/nbnull.png", A_Middle + A_Center));

	H3_Object_EnablePhysics(obj1, H3_BOX_COLLIDER(2, 50, 50, A_Middle + A_Center, true));
	H3_Object_EnablePhysics(obj2, H3_BOX_COLLIDER(2, 50, 50, A_Middle + A_Center, true));
	H3_Object_EnablePhysics(obj3, H3_BOX_COLLIDER(2, 50, 50, A_Middle + A_Center, true));
	H3_Object_EnablePhysics(obj4, H3_BOX_COLLIDER(2, 50, 50, A_Middle + A_Center, true));

	H3_Object_SetTranslation(obj1, screen_x / 2, screen_y / 2);
	H3_Object_SetTranslation(obj2, 900, 800);
	H3_Object_SetTranslation(obj3, 1000, 800);
	H3_Object_SetTranslation(obj4, 1100, 800);

	H3_Object_AddComponent(obj1, CLUECOMPONENT_CREATE(scn, h3, camera));

	///////////////////////////////////////


	//H3Handle digide = H3_Object_Create(scn, "digide", NULL);
	//H3_Object_AddComponent(digide, DIGIDE_CREATE(scn, nbcode1, nbcode2, nbcode3, nbcode4));



	float a; float b;
	do
	{
		exitGame = SMComponent_GetstateBtnExitEx(first_obj);
		if (SMComponent_GetstateBtnStartEx(first_obj))
		{
			iWantThis = 1;
		}
		if (SMComponent_GetstateBtnPlayerChooseEx(first_obj) && dontBtnMenu == 0)
		{
			iWantThis = 4;
		}


		if (iWantThis == 0)
		{
			scnTurn = H3_DoFrame(h3, scnMenu);
			dontBtnMenu = 0;
			CharacterComponent_SetwayPointEx(selectCharacter, 0);
		}
		if (iWantThis == 1)
		{
			scnTurn = H3_DoFrame(h3, scn);
		}
		if (iWantThis == 2)
		{
			scnTurn = H3_DoFrame(h3, scnFirstLunch);
			if (BootMenuComponent_GetwayPointEx(boot) == 1)
			{
				H3_Object_Destroy(boot, true);
				iWantThis = 3;
			}

		}
		if (iWantThis == 3)
		{
			scnTurn = H3_DoFrame(h3, scnFirstLunch);
			if (stateMenu == 0)
			{
				stateMenu = 3;

				H3_Object_AddComponent(credit, CREDITCOMPONENT_CREATE(scnFirstLunch, stateMenu));
			}
			if (CreditComponent_GetwayPointEx(credit) == 1)
			{
				H3_Scene_Destroy(scnFirstLunch);
				iWantThis = 0;
			}

		}
		if (iWantThis == 4)
		{
			scnTurn = H3_DoFrame(h3, scnMenuChoose);
			H3_Object_SetTranslation(selectCharacterCamera, 960, 540);
			if (CharacterComponent_GetwayPointEx(selectCharacter) == 1)
			{
				iWantThis = 0;
				dontBtnMenu = 1;
			}
		}



	} while (scnTurn && exitGame == false);



	return 0;
}



