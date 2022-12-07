#include <h3.h>
#include <stdio.h>
#include <components/cameracomponent.h>
#include <components/spritecomponent.h>
#include <player.h>

#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG

int main(int argc, char** argv)
{
	int screen_x = 1920;
	int screen_y = 1080;

	H3Handle h3 = H3_Init((SH3InitParams) {
		.width = screen_x,
			.height = screen_y,
			.fullscreen = false,
			.windowTitle = "Magazin",
	});

	H3Handle scene = H3_Scene_Create(h3, true);

	H3Handle camera = H3_Object_Create(scene, "camera", NULL);
	H3_Object_AddComponent(camera, CAMERACOMPONENT_CREATE(screen_x, screen_y));

	H3Handle player = H3_Object_Create(scene, "player", NULL);
	H3_Object_AddComponent(player, PLAYER_CREATE(camera));

	do  {
		
	} while (H3_DoFrame(h3, scene));
}
