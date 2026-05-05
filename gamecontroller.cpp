#include "board.h"
#include "snake.h"
// #include "food.h"
#include "gamecontroller.h"
#include "EmptyCellTracker.h"


GameController::GameController(int size , int dfclty) : board(size), snake(size/2 , size/2)
                                                        , tracker(size), NFoodCount(0)
                                                        , difficulty(dfclty)
{
    board[size/2][size/2] = CellContent::body;
    createFood();
}


void GameController::createFood()
{
    NFoodCount++;

    auto[x,y] = tracker.getRandomEmptyCell();

    if(NFoodCount > 5)
    {
        NFoodCount = 0;
        board[x][y] = CellContent::Sfood;
    }
    board[x][y] = CellContent::Nfood;
}

void GameController::changeDirection(Direction direction)
{
    Direction currentDirection = snake.getDirection();
    
    switch (direction)
    {
        case Direction::UP:
            if (currentDirection == Direction::DOWN) { return; }
            break;

        case Direction::DOWN:
            if (currentDirection == Direction::UP) { return; }
            break;

        case Direction::LEFT:
            if (currentDirection == Direction::RIGHT) { return; }
            break;

        case Direction::RIGHT:
            if (currentDirection != Direction::LEFT) { return; }
            break;
    }

    snake.setDirection(direction);

}

bool GameController::willHitBoundary() const
{
    auto currentHead = snake.getHead();
    Direction currentDir = snake.getDirection();

    int size = board.getSide();

    switch(currentDir)
    {
        case Direction::UP:
            if (currentHead.second == 0) return true;
            break;

        case Direction::DOWN:
            if (currentHead.second == size) return true;
            break;

        case Direction::LEFT:
            if (currentHead.first == 0) return true;
            break;

        case Direction::RIGHT:
            if (currentHead.first == size) return true;
            break;
    }

    return false;
}


void GameController::eat(int growth)
{
    auto nextHead = snake.getNextHead();
    snake.grow(growth);
    tracker.EmptyCellRemoval(nextHead.first, nextHead.second);
    board[nextHead.first][nextHead.second] = CellContent::body;
    createFood();
}




bool GameController::runStep()
{
    bool lose = false;

    auto nextHead = snake.getNextHead();
    auto currentTail = snake.getTail();
    
    // Conditions checks
    // 1. did it hit boundry
    if(willHitBoundary())
    {
        lose = true;
        return false;
    }    

    // 2. did it hit itself
    if(board[nextHead.first][nextHead.second] == CellContent::body )
    {
        lose = true;
        return false;
    }

    // 3. if(did it eat food)
    // Normal Food
    if(board[nextHead.first][nextHead.second] == CellContent::Nfood )
    {
        eat(1);
    }
    
    // Super Food
    else if(board[nextHead.first][nextHead.second] == CellContent::Sfood)
    {
        eat(3);
    }

    // move
    snake.move();

    // change the boarder cells (the occupied one and the released one)
    board[nextHead.first][nextHead.second] = CellContent::body;
    board[currentTail.first][currentTail.second] == CellContent::empty;

    return true;
}

