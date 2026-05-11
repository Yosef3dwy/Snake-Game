#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <utility>
#include "enums.h"

class Snake {
private:
    std::deque<std::pair<int, int>> body;
    Direction direction;

public:
    Snake(int x_init, int y_init);
    std::pair<int, int> getTail() const;
    std::pair<int, int> getHead() const;
    void setDirection(Direction direction);
    Direction getDirection() const;
    void move();
    void grow(int amount);
    int score();
    std::pair<int, int> getNextHead() const;
};

#endif // SNAKE_H
