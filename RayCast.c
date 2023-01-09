/*#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <RayCast.h>
#include <Player.h>

typedef struct
{
	H3Handle scene;
	float px;
	float py;
	float vx;
	float vy;
	int way;
	uint32_t id;
	bool init;
} RayCast_Properties;

void* RayCast_CreateProperties(H3Handle scene, float vx, float vy, uint32_t id)
{
	RayCast_Properties* properties = malloc(sizeof(RayCast_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->scene = scene;
	properties->init = true;
	properties->way = 0;
	properties->px = Player_Getplayer_xEx(H3_Object_Get(properties->scene, "player"));
	properties->py = Player_Getplayer_yEx(H3_Object_Get(properties->scene, "player"));
	properties->vx = vx;
	properties->vy = vy;
	properties->id = id;
	return properties;
}


void RayCast_Terminate(void* properties)
{
	free(properties);
}

void RayCast_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {
	RayCast_Properties* props = (RayCast_Properties*)properties;

	if (props->init) {

		H3_Object_EnablePhysics(object, H3_CIRCLE_COLLIDER(CDT_Static, 1, true));
		H3_Object_SetTranslation(object, props->px, props->py);
		H3_Object_AddVelocity(object, props->vx, props->vy);

		props->init = false;
	}

	if (props->way != 0) {
		H3_Object_SetEnabled(object, false);
	}
}

void RayCast_Trigger(H3Handle object, SH3Collision collision) {
	SH3Component* component = H3_Object_GetComponent(object, 0x50000001);
	RayCast_Properties* props = (RayCast_Properties*)(component->properties);
	if (collision.other , NULL) {
	}
	else if (H3_Object_HasComponent(collision.other , props->id)) {
		props->way = 1;
	}
	else {
		props->way = 2;
	}
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(RayCast, RAYCAST_TYPEID, int, way);*/

/*#include "Raycast.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include<components/spritecomponent.h>
#include "Zombies.h"
#include "Player.h"
#include "AI.h"

typedef struct
{
	int destroyer;
	H3Handle watchman;

} RayCastComponent_Properties;




void RayCastComponent_Terminate(void* properties)
{
	free(properties);
}



void* RayCastComponent_CreateProperties(H3Handle watchman)
{
	RayCastComponent_Properties* properties = malloc(sizeof(RayCastComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->destroyer = 0;
	properties->watchman = watchman;

	return properties;
}

typedef struct
{
	int choose_dir;
	time_t t;
	float timer;
	int go;
	float zx; float zy; float rotate; float zvx; float zvy; char buffer[100]; int index;
	float px; float py;
	float dirx; float diry;
	H3Handle scn; H3Handle player; H3Handle zombie;
	int speed_bullet;
	float norme_b; int chase; int life_z;



} AIComponent_Properties;




void RayCastComponent_Collision(H3Handle object, SH3Collision collision)
{
	SH3Component* component = H3_Object_GetComponent(object, RAYCASTCOMPONENT_TYPEID);
	RayCastComponent_Properties* props = (RayCastComponent_Properties*)(component->properties);

	props->destroyer = 1;

	if (collision.other == NULL)
	{

	}

	else if (H3_Object_HasComponent(collision.other, PLAYER_TYPEID))
	{
		if (H3_Object_HasComponent(props->watchman, AI_TYPEID))
		{
			SH3Component* componenta = H3_Object_GetComponent(props->watchman, AI_TYPEID);
			AIComponent_Properties* propsAI = (AIComponent_Properties*)(componenta->properties);

			propsAI->chase = 1;
		}

	}
}

void RayCastComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	RayCastComponent_Properties* props = (RayCastComponent_Properties*)properties;

	if (props->destroyer == 1)
	{
		H3_Object_Destroy(object, false);
	}
}*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <components/spritecomponent.h>
#include "Raycast.h"
#include "AI.h"
#include "Watchman.h"
#include "Player.h"


typedef struct
{
	bool destroy;
	H3Handle watchman;

} RayCast_Properties;


void* RayCast_CreateProperties(H3Handle watchman)
{
	RayCast_Properties* properties = malloc(sizeof(RayCast_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->destroy = false;
	properties->watchman = watchman;

	return properties;
}


void RayCast_Terminate(void* properties)
{
	free(properties);
}


void RayCast_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	RayCast_Properties* props = (RayCast_Properties*)properties;

	if (props->destroy)
	{
		H3_Object_Destroy(object, false);
	}
}


void RayCast_Collision(H3Handle obj, SH3Collision col)
{
	SH3Component* component = H3_Object_GetComponent(obj, RAYCAST_TYPEID);
	RayCast_Properties* props = (RayCast_Properties*)(component->properties);

	if (col.other == NULL)
	{
		props->destroy = true;
	}
	else if (H3_Object_HasComponent(col.other, PLAYER_TYPEID))
	{
		AI_SetchaseEx(props->watchman, 1);
		props->destroy = true;
	}
}
