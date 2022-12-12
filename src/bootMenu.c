#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <bootMenu.h>

typedef struct
{
    H3Handle h3;
    H3Handle bootLogoMenu;
    H3Handle bootLogoProjet;
    H3Handle bootLogoNameTeam;
    int stateMenu;
    int init;
    float speedLogoX;
    float speedLogoY;
    int wayPoint;
    float chronometer;
    int spawnPosX;
    int spawnPosY;

} BootMenuComponent_Properties;

void BootMenuComponent_Init(SH3Transform* transform, void** propertiesPtr)
{
//    BootMenuComponent_Properties* props = (BootMenuComponent_Properties*)propertiesPtr;
//
//    // START-UP BOOT //
//    H3Handle bootLogoMenu = H3_Object_Create(props->h3, "bootLogoMenu", NULL);
//    H3_Object_AddComponent(bootLogoMenu, SPRITECOMPONENT_CREATE("assets/Boot/logo_horizontal_HD_1920x1080.png", 0x22));
//    H3_Object_SetRenderOrder(bootLogoMenu, 1);
//    H3_Object_EnablePhysics(bootLogoMenu, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Center | A_Middle, false));
//    H3_Object_SetTranslation(bootLogoMenu, 0, 0);
}

void BootMenuComponent_Terminate(void* properties)
{
    free(properties);
}


void BootMenuComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    BootMenuComponent_Properties* props = (BootMenuComponent_Properties*)properties;
    props->chronometer;

    if (props->init == 0)
    {
        props->init = 1;
        if (props->stateMenu == 0)
        {
            // START-UP BOOT //
            // LOGO LaHorde //
            props->bootLogoMenu = H3_Object_Create2(props->h3, "bootLogoMenu", NULL, 1);
            H3_Object_AddComponent(props->bootLogoMenu, SPRITECOMPONENT_CREATE("assets/Boot/LaHorde_HorrorTheme_720x480.png", 0x22));

            H3_Object_EnablePhysics(props->bootLogoMenu, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Center | A_Middle, false));
            H3_Object_SetTranslation(props->bootLogoMenu, props->spawnPosX, props->spawnPosY);

            // LOGO CODE DU PROJET //
            props->bootLogoProjet = H3_Object_Create2(props->h3, "bootLogoProjet", NULL, 1);
            H3_Object_AddComponent(props->bootLogoProjet, SPRITECOMPONENT_CREATE("assets/Boot/CodeDuProjet_720x480.png", 0x22));

            H3_Object_EnablePhysics(props->bootLogoProjet, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Center | A_Middle, false));
            H3_Object_SetTranslation(props->bootLogoProjet, props->spawnPosX + 1000, props->spawnPosY);

            // LOGO NAME TEAM //
            props->bootLogoNameTeam = H3_Object_Create2(props->h3, "bootLogoNameTeam", NULL, 1);
            H3_Object_AddComponent(props->bootLogoNameTeam, SPRITECOMPONENT_CREATE("assets/Boot/NomTeam_720x480.png", 0x22));

            H3_Object_EnablePhysics(props->bootLogoNameTeam, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Center | A_Middle, false));
            H3_Object_SetTranslation(props->bootLogoNameTeam, props->spawnPosX + 1700, props->spawnPosY + 20);
        }
    }


    if (props->stateMenu == 0 && props->init == 1)      //State menu = 0 -> first image
    {

        // ANIMATED LOGO BOOT MENU //
        float logoPosX, logoPosY;
        H3_Transform_GetPosition(H3_Object_GetTransform(props->bootLogoMenu), &logoPosX, &logoPosY);
        
        if (props->wayPoint == 0)
        {
            //printf("START-UP BOOT\n");
            H3_Object_SetVelocity(props->bootLogoMenu, props->speedLogoX, props->speedLogoY);
            H3_Object_SetVelocity(props->bootLogoProjet, props->speedLogoX, props->speedLogoY);
            H3_Object_SetVelocity(props->bootLogoNameTeam, props->speedLogoX, props->speedLogoY);
        }

        if (logoPosX <= - 2500 && logoPosX!=0 && props->wayPoint == 0)   // Way point to set definition -> right 
        {
            //props->wayPoint = 0;
            printf("Way Point : %d\n", props->wayPoint);
            //BootMenuComponent_SetstateMenuEx(props->stateMenu, 3);
            props->wayPoint = 1;
            
            /*H3_Object_SetTranslation(props->bootLogoMenu, props->spawnPosX, props->spawnPosY);
            H3_Object_SetTranslation(props->bootLogoProjet, props->spawnPosX + 1000, props->spawnPosY);
            H3_Object_SetTranslation(props->bootLogoNameTeam, props->spawnPosX + 1700, props->spawnPosY + 20);*/
        }
    }

}


void* BootMenuComponent_CreateProperties(H3Handle h3, int stateMenu)
{
    BootMenuComponent_Properties* properties = malloc(sizeof(BootMenuComponent_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->h3 = h3;
    properties->init = 0;
    properties->speedLogoX = - 400.0f;
    properties->speedLogoY = 0.0f;
    properties->wayPoint = 0;
    properties->spawnPosX = 1920 + 1920 / 2;
    properties->spawnPosY = 1080 /2;

    // MENU //
    properties->stateMenu = stateMenu;

    return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(BootMenuComponent, BOOTMENUCOMPONENT_TYPEID, int, wayPoint);