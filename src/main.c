#include <h3.h>
#include <components/spritecomponent.h>
#include "StartMenu.h"

#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG

int main(int argc, char** argv)
{
	H3Handle h3 = H3_Init((SH3InitParams) {
		.width = 1440,
			.height = 832,
			.fullscreen = false,
			.windowTitle = "Pandemic",
	});


	H3Handle scnStartMenu = H3_Scene_Create(h3, true);
	


	H3Handle StartMenu = H3_Object_Create(scnStartMenu, "menuController", NULL);
	H3_Object_AddComponent(StartMenu, MCCOMPONENT_CREATE(scnStartMenu, h3));

	/*H3_Object_SetEnabled(scn, false);*/

	//H3Handle player = H3_Object_Create2(scn, "player", NULL, 5);
	//H3Handle object = H3_Object_Create2(scn, "obj", NULL, 2);


	//H3_Object_AddComponent(player, SPRITECOMPONENT_CREATE("assets/player.png", A_Center + A_Middle));
	//H3_Object_EnablePhysics(player, H3_BOX_COLLIDER(2, 200, 200, A_Top | A_Middle, false));
	//H3_Object_EnablePhysics(object, H3_BOX_COLLIDER(2, 200, 200, A_Top | A_Middle, true));
	//H3_Object_AddComponent(player, PLAYERCOMPONENT_CREATE());
	//H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/obj.png", A_Center + A_Middle));

	//H3Handle object2 = H3_Object_Create2(scn, "obj2", NULL, 2);
	//H3_Object_EnablePhysics(object2, H3_BOX_COLLIDER(2, 200, 200, A_Top | A_Middle, true));
	//H3_Object_AddComponent(object2, SPRITECOMPONENT_CREATE("assets/obj.png", A_Center + A_Middle));

	//H3Handle object3 = H3_Object_Create2(scn, "obj3", NULL, 2);
	//H3_Object_EnablePhysics(object3, H3_BOX_COLLIDER(2, 200, 200, A_Top | A_Middle, true));
	//H3_Object_AddComponent(object3, SPRITECOMPONENT_CREATE("assets/obj.png", A_Center + A_Middle));
	//H3_Object_SetTranslation(object3, 100, 700);

	//H3_Object_SetTranslation(player, 100, 100);
	//H3_Object_SetTranslation(object, 500, 500);
	//H3_Object_SetTranslation(object2, 700, 700);


	do
	{

	} while (H3_DoFrame(h3, scnStartMenu));

	return 0;
}
