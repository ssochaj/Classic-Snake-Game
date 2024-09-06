#include "Player.h"


Player::Player(GameMechs* thisGMRef) : mainGameMechsRef(thisGMRef)
{
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    char input = mainGameMechsRef->getInput();

    if(input != 0)
        switch(input)
        {
            // move up
            case 'w':
                if (myDir != UP && myDir != DOWN)
                    myDir = UP;
                break;

            // move left
            case 'a':
                if (myDir != LEFT && myDir != RIGHT)
                    myDir = LEFT;
                break;

            // move down
            case 's':
                if (myDir != UP && myDir != DOWN)
                    myDir = DOWN;
                break;

            // move right
            case 'd':
                if(myDir != LEFT && myDir != RIGHT)
                    myDir = RIGHT;
                break;
            
            default:
                break;
        }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos currHead; // holding the pos information of the current head
    playerPosList->getHeadElement(currHead);

    switch(myDir)
    {
        case LEFT:
            currHead.x--;
            if(currHead.x <= 0)
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2; 
            break;
        
        case RIGHT:
            currHead.x++;
            if(currHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
                currHead.x = 1;
            break;
        
        case UP:
            currHead.y--;
            if(currHead.y <= 0)
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            break;

        case DOWN:
            currHead.y++;
            if (currHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
                currHead.y = 1;  
            break;
        
        case STOP:
        default:
            break;  
    }

    
    // if new head position overlaps with food
    objPos tempFoodPos;
    mainGameMechsRef->getFoodPos(tempFoodPos);

    // if player reaches food, generate new food position
    if(currHead.isPosEqual(&tempFoodPos))
    {
        mainGameMechsRef->generateFood(currHead);
        mainGameMechsRef->incrementScore();
    }
    else
    {
        // check collision with player's body
        for (int i = 1; i < playerPosList->getSize(); i++)
        {
            objPos tempBody;
            playerPosList->getElement(tempBody, i);
            // if head pos collides with player body
            if (currHead.isPosEqual(&tempBody))
            {
                // end game (user lost)
                mainGameMechsRef->setLoseFlag();
                return; // exit loop and function = game is lost
            }
        }

        if (mainGameMechsRef->getScore() >= playerPosList->getSize())
        {
            // if score is greater than size, insert new head without removing tail
            playerPosList->insertHead(currHead);
        }
        else
        {
            // score is same, remove tail to keep constant length
            playerPosList->insertHead(currHead);
            playerPosList->removeTail();
        }
    }
}
