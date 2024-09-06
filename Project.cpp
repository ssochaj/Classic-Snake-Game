#include <iostream>
#include "MacUILib.h"
#include "objPos.h" // fundamental building block for project
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

// OOD Benefit - very limited global var declaration
// in advanced OOD, you don't need global variable
GameMechs* myGM;
Player* myPlayer;
objPos myPos;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(26, 13); // make the board size 26x13
    myPlayer =  new Player(myGM);

    objPos tempPos(-1,-1,'o');
    myGM->generateFood(tempPos);

    // Think about when to generate the new food...

    // Think about whether you want to set up a debug key to call the 
    //    food generation routine for verification

    // remember, generateFood() requires player reference. You will need to 
    //     provide it AFTER player object is instantiated

    // this is a makeshift setup so i don't have to touch generateItem yet
    // you need to do this yourself
    // objPos tempPos(-1, -1, 'o');
    // myGM->generateFood(tempPos); // turn this into array list operation

}

void GetInput(void)
{
    myGM -> getInput();
}

void RunLogic(void)
{
    // char input = myGM->getInput();
    
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    // Check if the player has reached the food
    /*
    objPos tempFoodPos;
    myGM->getFoodPos(tempFoodPos);

    if (tempPos.isPosEqual(&tempFoodPos))
    {
        // Player reached the food, generate a new food position
        myGM->generateFood(tempPos);
        myGM->incrementScore();
    }
    */

    myGM->clearInput(); // so not to repeatedly process the input
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos tempFoodPos;
    if (!myGM->hasFoodGeneratedThisFrame())
    {
        myGM->generateFood(tempBody);
    }

    myGM->getFoodPos(tempFoodPos);

    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            bool drawn = false;
            
            // iterate through every element in list
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if(tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            
            if(drawn) continue;
            // if player body was drawn, don't draw anything below.

            // draw border
            if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            // include food into draw routine
            else if (j == tempFoodPos.x && i == tempFoodPos.y)
            {
                MacUILib_printf("%c", tempFoodPos.getSymbol());
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Food Pos: <%d, %d>\n", tempFoodPos.x, tempFoodPos.y);
    // Because we are  using the async input in MacUILib, we have to use MacUILib_printf() instead of cout

    if (myGM->getLoseFlagStatus())
    {
        MacUILib_clearScreen();
        MacUILib_printf("YOU LOST!!!!\n");
         MacUILib_printf("Press ESC to exit.");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_uninit();

    // remove heap instances
    delete myGM;
    delete myPlayer;
}
