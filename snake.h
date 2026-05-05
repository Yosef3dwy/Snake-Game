#ifndef SNAKE_H
#define SNAKE_H

class Snake {
private:
    std::deque<std::pair<int, int>> body;
    Direction direction;

public:
    Snake(int x_init, int y_init);
    std::pair<int, int> getTail();
    std::pair<int, int> getHead();
    void setDirection(Direction direction);
    Direction getDirection();
    void move();
    void grow(int amount);
    int score();
};

#endif // SNAKE_H