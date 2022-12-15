#include "Object.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <components/spritecomponent.h>
#include <components/maplayercomponent.h>
#include <components/cameracomponent.h>
#include "Monstere.h"
#include "Clue.h"
#include "Timer.h"
#include "TypeWeapon.h"
#include "TypeMonstere.h"
#include "TypeCanTake.h"
#include "TypeKey.h"

typedef struct
{
	H3Handle monstere; H3Handle scn; H3Handle cam; float condition; int monstereEffect; int init;
	H3Handle paperClue; H3Handle h3;  float cX; float cY; int* scnLunch; H3Handle malmart; H3Handle weapon;
	H3Handle monstereObj1; H3Handle monstereObj2; H3Handle monstereObj3; H3Handle door; H3Handle useKeyHere; H3Handle doorKey;

	int spawnRandomPos;
	int randPosX;
	int randPosY;


} ObjectComponent_Properties;




void ObjectComponent_Terminate(void* properties)
{

	free(properties);
}



void* ObjectComponent_CreateProperties(H3Handle scn, H3Handle h3, H3Handle cam, int* scnLunch)
{
	ObjectComponent_Properties* properties = malloc(sizeof(ObjectComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->init = 0;
	properties->scn = scn;
	properties->h3 = h3;
	properties->cam = cam;
	properties->monstere = H3_Object_Create(scn, "monstere", NULL);
	properties->paperClue = H3_Object_Create(scn, "paperClue", NULL);
	properties->weapon = H3_Object_Create(scn, "weapon", NULL);
	properties->malmart = H3_Object_Create2(scn, "malmart", NULL, 2);
	properties->monstereObj1 = H3_Object_Create(scn, "monstereObj1", NULL);
	properties->monstereObj2 = H3_Object_Create(scn, "monstereObj2", NULL);
	properties->monstereObj3 = H3_Object_Create(scn, "monstereObj3", NULL);
	properties->door = H3_Object_Create2(scn, "door", NULL, 2);
	properties->useKeyHere = H3_Object_Create(scn, "useKeyCanTake", NULL);
	properties->doorKey = H3_Object_Create2(scn, "doorKey", NULL, 2);


	properties->monstereEffect = 0;

	properties->scnLunch = scnLunch;

	return properties;
}

void UpObject(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	ObjectComponent_Properties* p = (ObjectComponent_Properties*)properties;
	H3_Transform_GetPosition(H3_Object_GetTransform(p->cam), &p->cX, &p->cY);
	if (*p->scnLunch == 1)
	{
		if (p->init == 0)
		{
			p->init = 1;


			// spawn table monstere
			int tab [5][3] = {	{440, 970, 0}, // caisse
								{309, 788, 0}, //box
								{544, 521, 0}, // rayon
								{660, 354, 0}, //haut
								{880, 1180, 0} }; //bas 

			int index = rand() % 4;
			printf("%d this\n", tab[0][2]);

			H3_Object_AddComponent(p->monstere, MONSTERECOMPONENT_CREATE(object));
			H3_Object_AddComponent(p->monstere, TYPECANTAKE_CREATE());
			H3_Object_AddComponent(p->monstere, TIMERCOMPONENT_CREATE(p->scn, p->cam, object));

			H3_Object_AddComponent(p->weapon, SPRITECOMPONENT_CREATE("assets/baguette.png", A_Center + A_Middle));
			H3_Object_AddComponent(p->weapon, TYPEWEAPON_CREATE());
			H3_Object_AddComponent(p->weapon, TYPECANTAKE_CREATE());
			H3_Object_EnablePhysics(p->weapon, H3_BOX_COLLIDER(2, 50, 50, A_Center + A_Middle, true));
			H3_Object_SetTranslation(p->weapon, 1050, 1000);





			H3_Object_AddComponent(p->monstereObj1, SPRITECOMPONENT_CREATE("assets/monstère.png", A_Center + A_Middle));
			H3_Object_AddComponent(p->monstereObj1, TYPEMONSTERE_CREATE());
			H3_Object_AddComponent(p->monstereObj1, TYPECANTAKE_CREATE());
			H3_Object_EnablePhysics(p->monstereObj1, H3_BOX_COLLIDER(2, 50, 50, A_Center + A_Middle, true));
			H3_Object_SetTranslation(p->monstereObj1, tab[index][0], tab[index][1]);
			printf("%d this\n", tab[0][1]);
			tab[index][2] = 1;

			index = rand() % 5;
			while (tab[index][2] == 1)
			{
				index = rand() % 5;
			}

			H3_Object_AddComponent(p->monstereObj2, SPRITECOMPONENT_CREATE("assets/monstère.png", A_Center + A_Middle));
			H3_Object_AddComponent(p->monstereObj2, TYPEMONSTERE_CREATE());
			H3_Object_AddComponent(p->monstereObj2, TYPECANTAKE_CREATE());
			H3_Object_EnablePhysics(p->monstereObj2, H3_BOX_COLLIDER(2, 50, 50, A_Center + A_Middle, true));
			H3_Object_SetTranslation(p->monstereObj2, tab[index][0], tab[index][1]);
			printf("%d this\n", tab[0][1]);
			tab[index][2] = 1;

			index = rand() % 5;
			while (tab[index][2] == 1)
			{
				index = rand() % 5;
			}

			H3_Object_AddComponent(p->monstereObj3, SPRITECOMPONENT_CREATE("assets/monstère.png", A_Center + A_Middle));
			H3_Object_AddComponent(p->monstereObj3, TYPEMONSTERE_CREATE());
			H3_Object_AddComponent(p->monstereObj3, TYPECANTAKE_CREATE());
			H3_Object_EnablePhysics(p->monstereObj3, H3_BOX_COLLIDER(2, 50, 50, A_Center + A_Middle, true));
			H3_Object_SetTranslation(p->monstereObj3, tab[index][0], tab[index][1]);
			printf("%d this\n", tab[0][1]);
			tab[index][2] = 1;

			index = rand() % 5;
			while (tab[index][2] == 1)
			{
				index = rand() % 5;
			}




			H3_Object_AddComponent(p->paperClue, SPRITECOMPONENT_CREATE("assets/trash.png", A_Center + A_Middle));
			H3_Object_AddComponent(p->paperClue, CLUECOMPONENT_CREATE(p->scn, p->h3, p->cam));
			H3_Object_EnablePhysics(p->paperClue, H3_BOX_COLLIDER(2, 50, 50, A_Center + A_Middle, true));
			H3_Object_SetTranslation(p->paperClue, 785, 350);
			
			H3_Object_AddComponent(p->door, SPRITECOMPONENT_CREATE("assets/door.png", A_Center + A_Middle));
			H3_Object_EnablePhysics(p->door, H3_BOX_COLLIDER(CDT_Static, 50, 30, A_Top + A_Middle, false));
			H3_Object_SetTranslation(p->door, 1072, 325);

			H3_Object_EnablePhysics(p->useKeyHere, H3_BOX_COLLIDER(CDT_Static, 60, 90, A_Center + A_Middle, true));
			H3_Object_AddComponent(p->useKeyHere, TYPEKEY_CREATE());
			H3_Object_SetTranslation(p->useKeyHere, 1072, 325);

			H3_Object_AddComponent(p->doorKey, SPRITECOMPONENT_CREATE("assets/key.png", A_Center + A_Middle));
			H3_Object_EnablePhysics(p->doorKey, H3_BOX_COLLIDER(2, 50, 30, A_Top + A_Middle, true));
			H3_Object_AddComponent(p->doorKey, TYPECANTAKE_CREATE());
			H3_Object_AddComponent(p->doorKey, TYPEKEY_CREATE());
			H3_Object_SetTranslation(p->doorKey, 900, 900);

			H3_Object_AddComponent(p->malmart, SPRITECOMPONENT_CREATE("assets/magazin_enseigne.png", A_Center + A_Middle));

			
		}
		H3_Object_SetTranslation(p->malmart, 1260, 1050);

	}
	
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ObjectComponent, OBJECTCOMPONENT_TYPEID, int, monstereEffect);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ObjectComponent, OBJECTCOMPONENT_TYPEID, H3Handle, monstere);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ObjectComponent, OBJECTCOMPONENT_TYPEID, H3Handle, monstereObj1);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ObjectComponent, OBJECTCOMPONENT_TYPEID, H3Handle, door);
