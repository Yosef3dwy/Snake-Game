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

std::pair<int, int> Snake::getTail() const
{
    return body.back();
}

std::pair<int, int> Snake::getHead() const
{
    return body.front();
}

void Snake::move()
{
    auto [x_t, y_t] = this->getNextHead();
    body.push_front(std::make_pair(x_t, y_t));
    body.pop_back();
}

void Snake::grow(int amount)
{

    auto [nx, ny] = getNextHead();
    for (int i = 0; i < amount; ++i)
        body.push_front(std::make_pair(nx, ny));
}

Direction Snake::getDirection() const
{
    return direction;
}

int Snake::score()
{
    return static_cast<int>(body.size()) - 1;
}

std::pair<int, int> Snake::getNextHead() const
{
    int x_t = body.front().first;
    int y_t = body.front().second;

    if      (direction == Direction::RIGHT) { x_t++; }
    else if (direction == Direction::LEFT ) { x_t--; }
    else if (direction == Direction::UP   ) { y_t--; }
    else if (direction == Direction::DOWN ) { y_t++; }

    return std::make_pair(x_t, y_t);
}
