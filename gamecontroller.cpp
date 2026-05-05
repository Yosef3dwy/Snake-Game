#include "board.h"
#include "snake.h"
#include "gamecontroller.h"
#include "emptycelltracker.h"

GameController::GameController(int size, int dfclty)
    : board(size),
    snake(size / 2, size / 2),
    tracker(size),
    NFoodCount(0),
    difficulty(dfclty)
{
    // Snake starts at (col=size/2, row=size/2)
    // board[row][col]
    board[size / 2][size / 2] = CellContent::body;
    tracker.EmptyCellRemoval(size / 2, size / 2);
    createFood();
}

// ─── createFood ──────────────────────────────────────────────────────────────
void GameController::createFood()
{
    NFoodCount++;
    std::pair<int, int> cell;

    // Guard against stale tracker entries by confirming the board cell is still empty.
    do {
        cell = tracker.getRandomEmptyCell();   // x=col, y=row
        if (board[cell.second][cell.first] == CellContent::empty) {
            break;
        }
        tracker.EmptyCellRemoval(cell.first, cell.second);
    } while (true);

    int x = cell.first;
    int y = cell.second;

    if (NFoodCount > 5) {
        NFoodCount = 0;
        board[y][x] = CellContent::Sfood;
    } else {
        board[y][x] = CellContent::Nfood;
    }
    tracker.EmptyCellRemoval(x, y);
}

// ─── changeDirection ─────────────────────────────────────────────────────────
void GameController::changeDirection(Direction direction)
{
    Direction cur = snake.getDirection();

    // Prevent reversing
    if (direction == Direction::UP    && cur == Direction::DOWN)  return;
    if (direction == Direction::DOWN  && cur == Direction::UP)    return;
    if (direction == Direction::LEFT  && cur == Direction::RIGHT) return;
    if (direction == Direction::RIGHT && cur == Direction::LEFT)  return;

    snake.setDirection(direction);
}

// ─── willHitBoundary ─────────────────────────────────────────────────────────
bool GameController::willHitBoundary() const
{
    auto [x, y] = snake.getHead();   // x=col, y=row
    int size = board.getSide();
    Direction dir = snake.getDirection();

    if (dir == Direction::UP    && y == 0)        return true;
    if (dir == Direction::DOWN  && y == size - 1) return true;
    if (dir == Direction::LEFT  && x == 0)        return true;
    if (dir == Direction::RIGHT && x == size - 1) return true;

    return false;
}

// ─── eat ─────────────────────────────────────────────────────────────────────
void GameController::eat(int growth)
{
    auto [nx, ny] = snake.getNextHead();   // next position (col, row)
    snake.grow(growth);
    board[ny][nx] = CellContent::body;
    createFood();
}

// ─── runStep ─────────────────────────────────────────────────────────────────
bool GameController::runStep()
{
    if (willHitBoundary()) return false;

    auto [nx, ny] = snake.getNextHead();
    auto [tx, ty] = snake.getTail();

    // Hit itself?
    if (board[ny][nx] == CellContent::body) return false;

    // Eat food?
    CellContent nextCell = board[ny][nx];
    if (nextCell == CellContent::Nfood) { eat(1); return true; }
    if (nextCell == CellContent::Sfood) { eat(3); return true; }

    // Normal move
    snake.move();
    board[ny][nx] = CellContent::body;
    board[ty][tx] = CellContent::empty;
    tracker.EmptyCellAddition(tx, ty);

    return true;
}

// ─── helpers ─────────────────────────────────────────────────────────────────
int GameController::getScore() const
{
    return const_cast<Snake &>(snake).score();
}

std::pair<int, int> GameController::getHead() const
{
    return snake.getHead();   // (col, row)
}