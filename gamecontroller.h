#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "snake.h"
#include "emptycelltracker.h"
#include "enums.h"

class GameController {
private:
    Snake snake;
    EmptyCellTracker tracker;
    int NFoodCount;
    int difficulty;

    void createFood();
    bool willHitBoundary() const;
    void eat(int growth);

public:
    Board board;

    GameController(int size, int dfclty);

    void changeDirection(Direction direction);
    bool runStep();

    int getScore() const;
    std::pair<int,int> getHead() const;
};

#endif // GAMECONTROLLER_H