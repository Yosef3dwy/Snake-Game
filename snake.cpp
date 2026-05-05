#include <iostream>
#include <deque>
#include "enums.h"
#include "snake.h"

Snake::Snake(int x_init, int y_init)
{
    direction = Direction::RIGHT;
    body.push_back(std::make_pair(x_init, y_init));
}

void Snake::setDirection(Direction direction)
{
    this->direction = direction;
}

std::pair<int, int> Snake::getTail()
{
    return body.back();
}

std::pair<int, int> Snake::getHead()
{
    return body.front();
}

void Snake::move()
{
    int x_t = body.front().first;
    int y_t = body.front().second;
    
    if      (direction == Direction::RIGHT) { x_t++; }
    else if (direction == Direction::LEFT ) { x_t--; }
    else if (direction == Direction::UP   ) { y_t--; }
    else if (direction == Direction::DOWN ) { y_t++; }
    
    body.push_front(std::make_pair(x_t, y_t));
    body.pop_back();
}

void Snake::grow(int amount)
{
    int x_t = body.front().first;
    int y_t = body.front().second;

    if      (direction == Direction::RIGHT) { x_t++; }
    else if (direction == Direction::LEFT ) { x_t--; }
    else if (direction == Direction::UP   ) { y_t--; }
    else if (direction == Direction::DOWN ) { y_t++; }
    
    body.push_front(std::make_pair(x_t, y_t));
}

Direction Snake::getDirection()
{
    return direction;
}

int Snake::score()
{
    return body.size() - 1;
}