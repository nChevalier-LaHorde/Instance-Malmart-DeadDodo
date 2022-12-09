#include <h3.h>
#include <stdio.h>
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
	H3Handle h3 = H3_Init((SH3InitParams) {
		.width = 1920,
			.height = 1080,
			.fullscreen = false,
			.windowTitle = "Worms",
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

