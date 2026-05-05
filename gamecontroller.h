#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {
private:
    Board board;
    Snake snake;
    int NFoodCount;

    Ifood* createFood();
    std::pair<int, int> generateRandomPos();


public:
    GameController(int size);
    void startGame(int difficulty, int size);
    void changeDirection(int direction);
    void pauseGame();
    void resumeGame();
    void restartGame();
};

#endif // GAMECONTROLLER_H
