#include <h3.h>
#include <stdio.h>
#include <time.h>
#include <components/cameracomponent.h>
#include <components/spritecomponent.h>
#include <Player.h>
#include <Digide.h>
#include <math.h>
#include <components/spritecomponent.h>
#include <components/maplayercomponent.h>
#include <components/textcomponent.h>
#include "StartMenu.h"
#include "Object.h"

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
	int iWantThis = 1;
	H3Handle scnMenu = H3_Scene_Create(h3, true);
	H3Handle scn = H3_Scene_Create(h3, true);

	H3Handle first_obj = H3_Object_Create(scnMenu, "first_obj", NULL);
	H3_Object_AddComponent(first_obj, SMCOMPONENT_CREATE(h3, scnMenu));

	H3Handle second_obj = H3_Object_Create(scn, "second_obj", NULL);
	H3_Object_AddComponent(second_obj, OBJECTCOMPONENT_CREATE(scn, h3));

	H3Handle camera = H3_Object_Create(scene, "camera", NULL);
	H3_Object_AddComponent(camera, CAMERACOMPONENT_CREATE(screen_x, screen_y));

	H3Handle player = H3_Object_Create(scene, "player", NULL);
	H3_Object_AddComponent(player, PLAYER_CREATE(camera));

	H3Handle digide = H3_Object_Create(scene, "digide", NULL);
	H3_Object_AddComponent(digide, DIGIDE_CREATE(scene, nbcode1, nbcode2, nbcode3, nbcode4));




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
		
		
	} while (scnTurn);



	return 0;
}

