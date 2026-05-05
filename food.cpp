#include "food.h"

Ifood::Ifood(int x, int y)
{
    position.first = x;
    position.second = y;
}

NormalFood::NormalFood(int x, int y) : Ifood(x , y) {}

std::pair<int, int> NormalFood::getPosition() const { return position; }

SuperFood::SuperFood(int x, int y) : Ifood(x , y) {}

std::pair<int, int> SuperFood::getPosition() const { return position; }