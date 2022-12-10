#include <h3.h>
#include <stdio.h>
<<<<<<< Updated upstream
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
=======
#include <stdlib.h>
#include <bootMenu.h>
#include <credit.h>
#include <chooseCharacter.h>
>>>>>>> Stashed changes

#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG


int main(int argc, char** argv)
{
<<<<<<< Updated upstream

	srand(time(NULL));
	int screen_x = 1920;
	int screen_y = 1080;
	int nbcode1 = rand() %9 +1;
	int nbcode2 = rand() %9 +1;
	int nbcode3 = rand() %9 +1;
	int nbcode4 = rand() %9 +1;

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
	int iWantThis = 0;
	H3Handle scnMenu = H3_Scene_Create(h3, true);
	H3Handle scn = H3_Scene_Create(h3, true);

	H3Handle first_obj = H3_Object_Create(scnMenu, "first_obj", NULL);
	H3_Object_AddComponent(first_obj, SMCOMPONENT_CREATE(h3, scnMenu));

	H3Handle second_obj = H3_Object_Create(scn, "second_obj", NULL);
	H3_Object_AddComponent(second_obj, OBJECTCOMPONENT_CREATE(scn, h3));

	H3Handle camera = H3_Object_Create(scn, "camera", NULL);
	H3_Object_AddComponent(camera, CAMERACOMPONENT_CREATE(screen_x, screen_y));

	H3Handle player = H3_Object_Create(scn, "player", NULL);
	H3_Object_AddComponent(player, PLAYER_CREATE(camera));

	//H3Handle digide = H3_Object_Create(scn, "digide", NULL);
	//H3_Object_AddComponent(digide, DIGIDE_CREATE(scn, nbcode1, nbcode2, nbcode3, nbcode4));




	float a; float b;
	do
	{	
		if (iWantThis == 0)
		{
			scnTurn = H3_DoFrame(h3, scnMenu);
		}
		if (iWantThis == 1)
		{
			scnTurn = H3_DoFrame(h3, scn);
		}
		
		exitGame = SMComponent_GetstateBtnExitEx(first_obj);
		if (SMComponent_GetstateBtnStartEx(first_obj))
		{
			iWantThis = 1;
		}
		
	} while (scnTurn && exitGame == false);



	return 0;
}

=======
    int stateMenu = 1;

    // WINDOW //
    int height = 1080;
    int width = 1920;
    H3Handle h3 = H3_Init((SH3InitParams) {
        .fullscreen = false,
            .height = height,
            .width = width,
            .windowTitle = "Malmart"
    });
    H3Handle scene = H3_Scene_Create(h3, true);
    bool stateWindow = true;

    // boot ................. a implementer //
    H3Handle boot = H3_Object_Create(scene, "boot", NULL);
    H3_Object_AddComponent(boot, BOOTMENUCOMPONENT_CREATE(scene, stateMenu));

    // credit ............... a implementer //
    H3Handle credit = H3_Object_Create(scene, "credit", NULL);
    H3_Object_AddComponent(credit, CREDITCOMPONENT_CREATE(scene, stateMenu));

    //  menu character ...... a implementer//
    H3Handle selectCharacter = H3_Object_Create(scene, "selectCharacter", NULL);
    H3_Object_AddComponent(selectCharacter, CHARACTERCOMPONENT_CREATE(scene, stateMenu));

    //bool destroySceneSelectCharacter = false;

    // choose ............... a implementer //
    //H3Handle boyCharacter = H3_Object_Create(scene, "boyCharacter", NULL);
    //H3_Object_AddComponent(boot, CHARACTERCOMPONENT_CREATE(scene, stateMenu));


    // LOOP //
    do {

        stateWindow = H3_DoFrame(h3, scene);
    } while (stateWindow == true);

    return 0;
}
>>>>>>> Stashed changes
