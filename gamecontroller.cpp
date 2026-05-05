#include "board.h"
#include "snake.h"
#include "gamecontroller.h"
#include "emptycelltracker.h"

GameController::GameController(int size, int dfclty)
    : board(size), snake(size / 2, size / 2),
    tracker(size), NFoodCount(0), difficulty(dfclty)
{
    // Mark starting cell as occupied and remove from tracker
    board[size / 2][size / 2] = CellContent::body;
    tracker.EmptyCellRemoval(size / 2, size / 2);
    createFood();
}

void GameController::createFood()
{
    NFoodCount++;

    auto [x, y] = tracker.getRandomEmptyCell();

    if (NFoodCount > 5) {
        NFoodCount = 0;
        board[y][x] = CellContent::Sfood;  // FIX: was board[x][y], row=y col=x
    } else {
        board[y][x] = CellContent::Nfood;  // FIX: was missing else, always overwrote Sfood
    }

    tracker.EmptyCellRemoval(x, y);
}

void GameController::changeDirection(Direction direction)
{
    Direction currentDirection = snake.getDirection();

    switch (direction) {
    case Direction::UP:
        if (currentDirection == Direction::DOWN) return;
        break;
    case Direction::DOWN:
        if (currentDirection == Direction::UP) return;
        break;
    case Direction::LEFT:
        if (currentDirection == Direction::RIGHT) return;
        break;
    case Direction::RIGHT:
        if (currentDirection == Direction::LEFT) return;  // FIX: was != LEFT (inverted)
        break;
    }

    snake.setDirection(direction);
}

bool GameController::willHitBoundary() const
{
    auto currentHead = snake.getHead();
    Direction currentDir = snake.getDirection();
    int size = board.getSide();

    switch (currentDir) {
    case Direction::UP:    if (currentHead.second == 0)        return true; break;
    case Direction::DOWN:  if (currentHead.second == size - 1) return true; break;  // FIX: was size (off by 1)
    case Direction::LEFT:  if (currentHead.first  == 0)        return true; break;
    case Direction::RIGHT: if (currentHead.first  == size - 1) return true; break;  // FIX: was size (off by 1)
    }
    return false;
}

void GameController::eat(int growth)
{
    auto nextHead = snake.getNextHead();
    snake.grow(growth);
    // nextHead is now a new body cell; tail removal is NOT done on eat (snake grew)
    board[nextHead.second][nextHead.first] = CellContent::body;  // FIX: row=y, col=x
    // tracker removal already done in createFood; no removal needed here
    createFood();
}

bool GameController::runStep()
{
    auto nextHead    = snake.getNextHead();
    auto currentTail = snake.getTail();

    // 1. Hit boundary?
    if (willHitBoundary())
        return false;

    // 2. Hit itself?
    if (board[nextHead.second][nextHead.first] == CellContent::body)  // FIX: row=y col=x
        return false;

    // 3. Ate food?
    CellContent nextCell = board[nextHead.second][nextHead.first];

    if (nextCell == CellContent::Nfood) {
        eat(1);
        return true;  // eat() already calls snake.grow() and moves internally
    } else if (nextCell == CellContent::Sfood) {
        eat(3);
        return true;
    }

    // 4. Normal move
    snake.move();

    board[nextHead.second][nextHead.first] = CellContent::body;   // FIX: row=y col=x
    board[currentTail.second][currentTail.first] = CellContent::empty; // FIX: was == (comparison not assignment)
    tracker.EmptyCellAddition(currentTail.first, currentTail.second);

    return true;
}

int GameController::getScore() const
{
    return const_cast<Snake&>(snake).score();
}

std::pair<int, int> GameController::getHead() const
{
    return snake.getHead();
}