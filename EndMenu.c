#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <EndMenu.h>
#include <components/spritecomponent.h>

typedef struct
{
    //var
    H3Handle h3;
    H3Handle background;
    H3Handle btnExit;
    H3Handle btnPlayAgain;
    H3Handle nightshift;
    H3Handle win;
    H3Handle gameover;
    H3Handle camera;

    bool stateExit;
    bool statePlayAgain;
    bool playerAlive;
    bool playerWin;

    float btnx;
    float btny;
    float btnx2;
    float btny2;

    int mouseX;
    int mouseY;


} EndMenuComponent_Properties;

void EndMenuComponent_Init(SH3Transform* transform, void** propertiesPtr)
{

}

void EndMenuComponent_Terminate(void* properties)
{
    free(properties);
}

void EndMenuComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
    EndMenuComponent_Properties* props = (EndMenuComponent_Properties*)properties;

    // MENU GAMEOVER //
    static int a = 0; //print one time
    
    if (props->playerAlive == false)
    {
        if (a == 0)
        {
            //create sprite
            props->background = H3_Object_Create2(props->h3, "background25", props->camera, 100);
            props->btnExit = H3_Object_Create2(props->h3, "exit25", props->camera, 110);
            props->btnPlayAgain = H3_Object_Create2(props->h3, "play again25", props->camera, 110);
            props->stateExit = H3_Object_Create2(props->h3, "stateExit25", props->camera, 110);
            props->statePlayAgain = H3_Object_Create2(props->h3, "statePlayAgain25", props->camera, 110);
            props->nightshift = H3_Object_Create2(props->h3, "nightshift25", props->camera, 110); //name of game
            props->gameover = H3_Object_Create2(props->h3, "gameover25", props->camera, 110);

            //add sprite
            H3_Object_AddComponent(props->background, SPRITECOMPONENT_CREATE("assets/BG_GO.png", A_Center | A_Middle));
            H3_Object_AddComponent(props->btnExit, SPRITECOMPONENT_CREATE("assets/Exit2.png", A_Center | A_Middle));
            H3_Object_AddComponent(props->btnPlayAgain, SPRITECOMPONENT_CREATE("assets/Play Again.png", A_Center | A_Middle));
            H3_Object_AddComponent(props->nightshift, SPRITECOMPONENT_CREATE("assets/NomDu Jeu - Copy.png", A_Center | A_Middle));
            H3_Object_AddComponent(props->gameover, SPRITECOMPONENT_CREATE("assets/gameover.png", A_Center | A_Middle));

            //debug
            printf("Le joueur est mort\n");
            a = 1;
        }

        //position of sprite 
        H3_Object_SetTranslation(props->btnExit, 200.0f, 100.0f);
        H3_Object_SetTranslation(props->btnPlayAgain, -200.0f, 100.0f);
        H3_Object_SetTranslation(props->nightshift, 0.0f, -150.0f);
        H3_Object_SetTranslation(props->gameover, 0.0f, -115.0f);

        H3_Object_Scale(props->nightshift, 0.2f);

        if (H3_Input_IsMouseBtnPressed(K_Left) && props->playerAlive == false)
        {
            H3_Input_GetMousePos(h3, &props->mouseX, &props->mouseY);
            if (props->mouseX >= 1335 && props->mouseX <= 1785 && props->mouseY >= 750 && props->mouseY <= 930) //box of button
            {
                //debug
                printf("Exit");
            }

            if (props->mouseX >= 135 && props->mouseX <= 585 && props->mouseY >= 750 && props->mouseY <= 930) //box of button
            {
                //debug 
                printf("Play Again");
            }
        }
    }
    // MENU WIN //
    static int b = 0; //print one time 


    if (props->playerWin == false)
    {
        if (b == 0)
        {
            //create sprite
            props->background = H3_Object_Create2(props->h3, "background25", props->camera, 100);
            props->win = H3_Object_Create2(props->h3, "win25", props->camera, 110);
            props->nightshift = H3_Object_Create2(props->h3, "nightshift25", props->camera, 110);
            props->btnExit = H3_Object_Create2(props->h3, "exit25", props->camera, 110);

            //add sprite
            H3_Object_AddComponent(props->background, SPRITECOMPONENT_CREATE("assets/BG_GO.png", A_Center | A_Middle));
            H3_Object_AddComponent(props->win, SPRITECOMPONENT_CREATE("assets/Win.png", A_Center | A_Middle));
            H3_Object_AddComponent(props->nightshift, SPRITECOMPONENT_CREATE("assets/NomDu Jeu - Copy.png", A_Center | A_Middle));
            H3_Object_AddComponent(props->btnExit, SPRITECOMPONENT_CREATE("assets/Exit2.png", A_Center | A_Middle));

            //debug
            printf("Le joueur à gagne\n");
            b = 1;
        }

        //position of sprite
        H3_Object_SetTranslation(props->win, 0.0f, -120.0f);
        H3_Object_SetTranslation(props->nightshift, 0.0f, -150.0f);
        H3_Object_SetTranslation(props->btnExit, 0.0f, 100.0f);

        H3_Object_Scale(props->win, 0.3f);
        H3_Object_Scale(props->nightshift, 0.2f);


        if (H3_Input_IsMouseBtnPressed(K_Left) && props->playerWin == false)
        {
            H3_Input_GetMousePos(h3, &props->mouseX, &props->mouseY);
            if (props->mouseX >= 735 && props->mouseX <= 1185 && props->mouseY >= 750 && props->mouseY <= 930) //box of button
            {
                //debug
                printf("Exit");
            }
        }
    }
}

void* EndMenuComponent_CreateProperties(H3Handle h3, H3Handle camera)
{
    EndMenuComponent_Properties* properties = malloc(sizeof(EndMenuComponent_Properties));
    H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

    properties->camera = camera;
    properties->h3 = h3;
    properties->playerAlive = true;
    properties->playerWin = true;
    properties->stateExit = false;
    properties->statePlayAgain = false;

    return properties;
}
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(EndMenuComponent, ENDMENUCOMPONENT_TYPEID, bool, playerAlive);