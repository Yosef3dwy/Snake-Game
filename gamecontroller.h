#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "snake.h"
#include "emptycelltracker.h"
#include "enums.h"
#include <qobject.h>
#include <qwindowdefs.h>

class GameController : public QObject {
    Q_OBJECT
private:
    Snake            snake;
    EmptyCellTracker tracker;
    int              NFoodCount;
    int              difficulty;

    void createFood();
    bool willHitBoundary() const;
    void eat(int growth);

public:
    Board board;
    std::pair<int,int> getNextHead() const;
    GameController(int size, int dfclty);

    void changeDirection(Direction direction);
    bool runStep();

    int getScore() const;
    std::pair<int,int> getHead() const;   // returns (col, row) == (x, y)
signals:
    void foodEaten();

};

#endif // GAMECONTROLLER_H