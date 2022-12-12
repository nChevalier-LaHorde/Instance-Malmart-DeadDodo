#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <credit.h>

typedef struct
{
    H3Handle h3;
    H3Handle creditMenu;
    int stateMenu;
    int init;
    float speedLogoX;
    float speedLogoY;
    int wayPoint;
    int spawnCreditPosX;
    int spawnCreditPosY;

} CreditComponent_Properties;

void CreditComponent_Terminate(void* properties)
{
    free(properties);
}


void CreditComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    CreditComponent_Properties* props = (CreditComponent_Properties*)properties;

    // INIT //
    if (props->init == 0 && props->stateMenu == 3)
    {
        props->init = 1;
        if (props->stateMenu == 3)
        {
            // LOGO LaHorde //
            props->creditMenu = H3_Object_Create2(props->h3, "creditMenu", NULL, 1);
            H3_Object_AddComponent(props->creditMenu, SPRITECOMPONENT_CREATE("assets/Credit/Credit_instance_720x800.png", 0x22));

            H3_Object_EnablePhysics(props->creditMenu, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Center | A_Middle, false));
            H3_Object_SetTranslation(props->creditMenu, props->spawnCreditPosX, props->spawnCreditPosY);
        }
    }

    

    if (props->stateMenu == 3 && props->init == 1)      //State menu = 3 -> credit sheet
    {
        // ANIMATED Credit//
        float creditLogoPosX, creditLogoPosY;
        H3_Transform_GetPosition(H3_Object_GetTransform(props->creditMenu), &creditLogoPosX, &creditLogoPosY);

        if (props->wayPoint == 0)   // Way point to set definition -> right to left
        {
            H3_Object_SetVelocity(props->creditMenu, props->speedLogoX, props->speedLogoY);
        }
        if (creditLogoPosY <= -850 && creditLogoPosY !=0 && props->wayPoint == 0)
        {
            props->wayPoint = 1;
            printf("Way Point : %d\n", props->wayPoint);
            H3_Object_SetTranslation(props->creditMenu, props->spawnCreditPosX, props->spawnCreditPosY);
        }
    }

}


void* CreditComponent_CreateProperties(H3Handle h3, int stateMenu)
{
    CreditComponent_Properties* properties = malloc(sizeof(CreditComponent_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->h3 = h3;
    properties->init = 0;
    properties->speedLogoX = 0.0f;
    properties->speedLogoY = -150.0f;
    properties->wayPoint = 0;
    properties->spawnCreditPosX = 1920 / 2;
    properties->spawnCreditPosY = 1080 + 1080 / 2;
    properties->stateMenu = stateMenu;    

    return properties;
}
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(CreditComponent, CREDITCOMPONENT_TYPEID, int, wayPoint);