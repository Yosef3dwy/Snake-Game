#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

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

    void startGame();
    void changeDirection(Direction direction);
    void pauseGame();
    void resumeGame();
    void restartGame();

    bool runStep();



};

#endif // GAMECONTROLLER_H
