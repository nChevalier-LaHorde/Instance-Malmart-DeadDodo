#include <h3.h>
#include <stdio.h>
#include <time.h>
#include <components/cameracomponent.h>
#include <components/spritecomponent.h>
#include <Player.h>
#include <Digide.h>

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

	H3Handle scene = H3_Scene_Create(h3, true);

	H3Handle camera = H3_Object_Create(scene, "camera", NULL);
	H3_Object_AddComponent(camera, CAMERACOMPONENT_CREATE(screen_x, screen_y));

	H3Handle player = H3_Object_Create(scene, "player", NULL);
	H3_Object_AddComponent(player, PLAYER_CREATE(camera));

	H3Handle digide = H3_Object_Create(scene, "digide", NULL);
	H3_Object_AddComponent(digide, DIGIDE_CREATE(scene, nbcode1, nbcode2, nbcode3, nbcode4));

	do  {
		//printf("%d", nbcode1);
		//printf("%d", nbcode2);
		//printf("%d", nbcode3);
		//printf("%d\n", nbcode4);
	} while (H3_DoFrame(h3, scene));
}
