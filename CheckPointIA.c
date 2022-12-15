#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <CheckPointIA.h>

typedef struct
{
	H3Handle scene;
	float checkPointIA_x;
	float checkPointIA_y;
	H3Handle checkPoints[75];
	//float checkPointsCoor[75][2];
	char checkPointsName[5];
	bool init;
} CheckPointIA_Properties;

void* CheckPointIA_CreateProperties(H3Handle scene)
{
	CheckPointIA_Properties* properties = malloc(sizeof(CheckPointIA_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");
	properties->scene = scene;
	properties->init = true;
	return properties;
}


void CheckPointIA_Terminate(void* properties)
{
	free(properties);
}

void CheckPointIA_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties) {
	CheckPointIA_Properties* props = (CheckPointIA_Properties*)properties;

	if (props->init) {


		float tab[75][2] = { {271, 900}, {367, 900}, {466, 900}, {559, 900}, {655, 900}, {751, 900}, {847, 900}, {943, 900}, {943, 804}, {943, 628}, {943, 420}, {1039, 420}, {1135, 420}, {1279, 420}, {1279, 372},
		{ 1279, 452 }, { 1279, 548 }, { 1279, 644 }, { 1279, 740 }, { 1279, 836 }, { 1279, 932 }, { 1464, 932 }, { 1464, 836 }, { 1464, 740 }, { 1464, 644 }, { 1464, 548 }, { 1464, 452 }, { 1464, 372 }, { 1071, 420 }, { 847, 420 },
		{ 751, 420 }, { 655, 420 }, { 559, 420 }, { 463, 420 }, { 463, 580 }, { 463, 628 }, { 463, 696 }, { 463, 792 }, { 367, 792 }, { 271, 792 }, { 367, 696 }, { 271, 696 }, { 367, 580 }, { 271, 580 }, { 559, 628 },
		{ 655, 628 }, { 751, 628 }, { 847, 628 }, { 1039, 628 }, { 1135, 628 }, { 1279, 628 }, { 463, 964 }, { 495, 964 }, { 591, 964 }, { 687, 964 }, { 783, 964 }, { 879, 964 }, { 943, 964 }, { 975, 964 }, { 1279, 1156 },
		{ 975, 1156 }, { 879, 1156 }, { 783, 1156 }, { 687, 1156 }, { 591, 1156 }, { 495, 1156 }, { 1039, 804 }, { 1135, 804 }, { 1279, 804 }, { 1071, 164 }, { 1370, 164 }, { 470, 164 }, { 470, 100 }, { 111, 100 }, { 111, 452 } };

		for (int i = 0; i < 75; i++) {
			snprintf(props->checkPointsName, 5, "cp%d", i);
			props->checkPoints[i] = H3_Object_Create2(props->scene, props->checkPointsName, NULL, 5);
			H3_Object_AddComponent(props->checkPoints[i], SPRITECOMPONENT_CREATE("assets/bullet.png", A_Middle + A_Center));
			H3_Object_EnablePhysics(props->checkPoints[i], H3_CIRCLE_COLLIDER(CDT_Static, 3, true));
			H3_Object_SetTranslation(props->checkPoints[i], tab[i][0], tab[i][1]);
		}
		props->init = false;
	}
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(CheckPointIA, CHECKPOINTIA_TYPEID, float, checkPointIA_x);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(CheckPointIA, CHECKPOINTIA_TYPEID, float, checkPointIA_y);