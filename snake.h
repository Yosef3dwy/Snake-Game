#ifndef SNAKE_H
#define SNAKE_H

class Snake {
private:
    std::deque<std::pair<int, int>> body;
    int direction;

public:
    Snake();
    std::pair<int, int> getTail();
    std::pair<int, int> getHead();
    void setDirection(int direction);
    void getDirection(); // Note: Matches UML, though typically this would return an int
    void move();
    void grow(int amount);
    int score();
};

#endif // SNAKE_H
