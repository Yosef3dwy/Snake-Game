#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "board.h"
#include "snake.h"
#include "emptycelltracker.h"
#include "enums.h"

class GameController : public QObject {
    Q_OBJECT

private:
    Snake            snake;
    EmptyCellTracker tracker;
    int              NFoodCount;
    int              difficulty;

    int              m_dropInterval;   // steps between each tile drop
    int              m_stepsSinceDrop; // step counter
    bool m_dropTiles;
    void createFood();
    bool willHitBoundary() const;
    void eat(int growth);
    void dropTile();

public:
    Board board;

    GameController(int size, int dfclty, bool dropTiles);



    void changeDirection(Direction direction);
    bool runStep();

    int getScore() const;
    std::pair<int,int> getHead()     const;
    std::pair<int,int> getNextHead() const;

signals:
    void foodEaten();
};

#endif // GAMECONTROLLER_H
