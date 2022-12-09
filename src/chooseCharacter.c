#include <stdlib.h>
#include <stdio.h>
#include <components/spritecomponent.h>
#include <math.h>
#include <chooseCharacter.h>
#include <bootMenu.h>

typedef struct
{
    // state
    int stateMenu;
    int init;

    // important
    H3Handle h3;
    float speedX;
    float speedY;
    int wayPoint;


    // input selection character
    int select;

    // boy character
    H3Handle boyCharacter;
    H3Handle boySelect;
    int spawnBoyCharacterPosX;
    int spawnBoyCharacterPosY;
    int widthBoyCharacter;
    int heightBoyCharacter;
    bool boySelectButton;
        // description
    H3Handle boyDescription;

    // girl character
    H3Handle girlCharacter;
    H3Handle girlSelect;
    int spawnGirlCharacterPosX;
    int spawnGirlCharacterPosY;
    int widthGirlCharacter;
    int heightGirlCharacter;
    bool girlSelectButton;
        // description
    H3Handle girlDescription;

} CharacterComponent_Properties;

void CharacterComponent_Terminate(void* properties)
{
    free(properties);
}


void CharacterComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    CharacterComponent_Properties* props = (CharacterComponent_Properties*)properties;


    // INIT //
    if (props->init == 0 && props->stateMenu == 1)
    {
        props->init = 1;
        if (props->stateMenu == 1)
        {
            // boy character 
            props->boyCharacter = H3_Object_Create2(props->h3, "boyCharacter", NULL, 1);
            H3_Object_AddComponent(props->boyCharacter, SPRITECOMPONENT_CREATE("assets/Choose character/boy.png", A_Left | A_Top));
            H3_Object_EnablePhysics(props->boyCharacter, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Middle| A_Center, false));
            H3_Object_SetTranslation(props->boyCharacter, props->spawnBoyCharacterPosX, props->spawnBoyCharacterPosY);
            // boy select
            props->boySelect = H3_Object_Create2(props->h3, "boySelect", NULL, 1);
            H3_Object_AddComponent(props->boySelect, SPRITECOMPONENT_CREATE("assets/Choose character/boy_select.png", A_Left | A_Top));
            H3_Object_EnablePhysics(props->boySelect, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Middle | A_Center, false));
            H3_Object_SetTranslation(props->boySelect, props->spawnBoyCharacterPosX, props->spawnBoyCharacterPosY);
            H3_Object_SetEnabled(props->boySelect, false);
                // boy description
            props->boyDescription = H3_Object_Create2(props->h3, "boyDescription", NULL, 1);
            H3_Object_AddComponent(props->boyDescription, SPRITECOMPONENT_CREATE("assets/Choose character/boy_description.png", A_Left | A_Top));
            H3_Object_SetTranslation(props->boyDescription, props->spawnBoyCharacterPosX * 1.8 , props->spawnBoyCharacterPosY + 510);
            H3_Object_SetEnabled(props->boyDescription, false);


            // girl character 
            props->girlCharacter = H3_Object_Create2(props->h3, "girlCharacter", NULL, 1);
            H3_Object_AddComponent(props->girlCharacter, SPRITECOMPONENT_CREATE("assets/Choose character/girl.png", A_Left | A_Top));
            H3_Object_EnablePhysics(props->girlCharacter, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Middle | A_Center, false));
            H3_Object_SetTranslation(props->girlCharacter, props->spawnGirlCharacterPosX, props->spawnGirlCharacterPosY);
            // girl select
            props->girlSelect = H3_Object_Create2(props->h3, "girlSelect", NULL, 1);
            H3_Object_AddComponent(props->girlSelect, SPRITECOMPONENT_CREATE("assets/Choose character/girl_select.png", A_Left | A_Top));
            H3_Object_EnablePhysics(props->girlSelect, H3_BOX_COLLIDER(CDT_Dynamic, 8, 8, A_Middle | A_Center, false));
            H3_Object_SetTranslation(props->girlSelect, props->spawnGirlCharacterPosX, props->spawnGirlCharacterPosY);
            H3_Object_SetEnabled(props->girlSelect, false);
                // girl description
            props->girlDescription = H3_Object_Create2(props->h3, "girlDescription", NULL, 1);
            H3_Object_AddComponent(props->girlDescription, SPRITECOMPONENT_CREATE("assets/Choose character/girl_description.png", A_Left | A_Top));
            H3_Object_SetTranslation(props->girlDescription, props->spawnGirlCharacterPosX * 1.2, props->spawnGirlCharacterPosY + 510);
            H3_Object_SetEnabled(props->girlDescription, false);
        }
    }


    // UPDATE //
    if (props->stateMenu == 1 && props->init == 1)      //State menu = 1 -> Selection character
    {
        printf("");
        // check mouse position
        int mousePosX, mousePosY;
        H3_Input_GetMousePos(h3, &mousePosX, &mousePosY);

                
        if (mousePosX >= props->spawnBoyCharacterPosX && mousePosX <= props->widthBoyCharacter && mousePosY >= props->spawnBoyCharacterPosY && mousePosY <= props->heightBoyCharacter)
        {
            props->select = 1;
        }
        
        else if (mousePosX >= props->spawnGirlCharacterPosX && mousePosX <= props->widthGirlCharacter && mousePosY >= props->spawnGirlCharacterPosY && mousePosY <= props->heightGirlCharacter)
        {
            props->select = 2;
        }

        else
        {
            props->select = 0;/*
            H3_Object_Destroy(props->boyDescription, false);
            H3_Object_Destroy(props->girlDescription, false);*/
        }
        // when the button pressed
        props->boySelectButton = H3_Button(h3, SpriteComponent_GetTextureEx(props->boyCharacter), props->spawnBoyCharacterPosX, props->spawnBoyCharacterPosY, A_Left | A_Top);
        props->girlSelectButton = H3_Button(h3, SpriteComponent_GetTextureEx(props->girlCharacter), props->spawnGirlCharacterPosX, props->spawnGirlCharacterPosY, A_Left | A_Top);

        // switch button detected to 
        if (props->boySelectButton)
        {
            props->select = 4;
        }
        if (props->girlSelectButton)
        {
            props->select = 5;
        }


        // action to select
        switch (props->select)
        {                   // description and move up character
            // if any has select
            case 0:
                printf("character not select %d\n", props->select);
                //image select off
                //boy
                H3_Object_SetEnabled(props->boyCharacter, true);
                H3_Object_SetEnabled(props->boySelect, false);
                //girl
                H3_Object_SetEnabled(props->girlCharacter, true);
                H3_Object_SetEnabled(props->girlSelect, false);

                // image description
                H3_Object_SetEnabled(props->boyDescription, false);
                H3_Object_SetEnabled(props->girlDescription, false);
                break;

            // boy
            case 1:
                printf("boy character %d\n", props->select);
                // image select boy
                H3_Object_SetEnabled(props->boyCharacter, false);
                H3_Object_SetEnabled(props->boySelect, true);
                H3_Object_SetEnabled(props->boyDescription, true);
                break;

            // girl
            case 2: 
                printf("girl character %d\n", props->select);
                //image select
                H3_Object_SetEnabled(props->girlCharacter, false);
                H3_Object_SetEnabled(props->girlSelect, true);
                H3_Object_SetEnabled(props->girlDescription, true);
                break;

                            // effect apply
            // boy effect
            case 4:
                printf("boy character select %d\n", props->select);
                // animation exit select chamber character
                props->select = 10;
                // boy action
                H3_Object_SetEnabled(props->boyCharacter, true);
                H3_Object_SetEnabled(props->boyDescription, true);

                // girl action
                H3_Object_SetEnabled(props->girlCharacter, false);
                H3_Object_SetEnabled(props->girlDescription, false);
                break;
               
            // girl effect
            case 5:
                printf("girl character select %d\n", props->select);
                // animation exit select chamber character
                props->select = 10;
                // boy select
                H3_Object_SetEnabled(props->boyCharacter, false);
                H3_Object_SetEnabled(props->boyDescription, false);

                // girl action
                H3_Object_SetEnabled(props->girlCharacter, true);
                H3_Object_SetEnabled(props->girlDescription, true);

                break;

            // enable to start
            case 10:
                printf("RETURN MENU");
                break;

            default:
                break;
        }





        //// animated character//
        //float boyCharacterPosX, boyCharacterPosY;
        //H3_Transform_GetPosition(H3_Object_GetTransform(props->boyCharacter), &boyCharacterPosX, &boyCharacterPosY);

        //// Way point to set definition -> right to left
        //if (props->wayPoint == 0)   
        //{
        //    H3_Object_SetVelocity(props->boyCharacter, props->speedX, props->speedY);
        //    printf("print boy character");
        //}
        //if (boyCharacterPosX <= -850 && boyCharacterPosX !=0 && props->wayPoint == 0)
        //{
        //    props->wayPoint = 0;
        //    printf("Way Point : %d\n", props->wayPoint);
        //    H3_Object_SetTranslation(props->boyCharacter, props->spawnBoyCharacterPosX, props->spawnBoyCharacterPosY);
        //}

        
    }
}


void* CharacterComponent_CreateProperties(H3Handle h3, int stateMenu)
{
    CharacterComponent_Properties* properties = malloc(sizeof(CharacterComponent_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->h3 = h3;
    properties->init = 0;
    properties->stateMenu = 1;

    //
    properties->speedX = 0.0f;
    properties->speedY = -150.0f;
    properties->wayPoint = 0;

    // switch character
    properties->select = 0;

    // boy character 
    properties->spawnBoyCharacterPosX = 1080 / 4;   
    properties->spawnBoyCharacterPosY = 70;
    properties->widthBoyCharacter = properties->spawnBoyCharacterPosX + 720;    // add width in pixel about the sprite
    properties->heightBoyCharacter = properties->spawnBoyCharacterPosY + 480;   // add height in pixel about the sprite

    // girl character 
    properties->spawnGirlCharacterPosX = properties->spawnBoyCharacterPosX + 750;
    properties->spawnGirlCharacterPosY = properties->spawnBoyCharacterPosY;
    properties->widthGirlCharacter = properties->spawnGirlCharacterPosX + 720;  // add width in pixel about the sprite
    properties->heightGirlCharacter = properties->spawnGirlCharacterPosY + 480;  // add height in pixel about the sprite
    

    return properties;
}