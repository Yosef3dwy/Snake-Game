#include "board.h"
#include "snake.h"
#include "food.h"
#include "gamecontroller.h"


GameController::GameController(int size) : board(size), snake(size/2 , size/2), NFoodCount(0) {}


Ifood* GameController::createFood()
{
    NFoodCount++;

    auto[x,y] = generateRandomPos();

    if(NFoodCount > 5)
    {
        NFoodCount = 0;
        return new SuperFood(x, y);
    }

    return new NormalFood(x, y);
}

std::pair<int, int> GameController::generateRandomPos()
{
    
}



void startGame(int difficulty, int size);
void changeDirection(int direction);
void pauseGame();
void resumeGame();
void restartGame();