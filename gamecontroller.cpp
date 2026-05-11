#include "board.h"
#include "snake.h"
#include "gamecontroller.h"
#include "emptycelltracker.h"

GameController::GameController(int size, int dfclty, bool dropTiles)
    : board(size),
      snake(size / 2, size / 2),
      tracker(size),
      NFoodCount(0),
      difficulty(dfclty),
      m_dropTiles(dropTiles),
      m_stepsSinceDrop(0)
{
    if      (dfclty == 1) m_dropInterval = 40;
    else if (dfclty == 3) m_dropInterval = 15;
    else                  m_dropInterval = 25;

    board[size / 2][size / 2] = body;
    tracker.EmptyCellRemoval(size / 2, size / 2);
    createFood();
}

// dropTile
void GameController::dropTile()
{
    if (!m_dropTiles)      return;
    if (tracker.isEmpty()) return;
    auto [x, y] = tracker.getRandomEmptyCell();
    board[y][x] = dropped;
    tracker.EmptyCellRemoval(x, y);
}

// createFood
void GameController::createFood()
{
    if (tracker.isEmpty()) return;

    NFoodCount++;
    auto [x, y] = tracker.getRandomEmptyCell();

    if (NFoodCount > 5) {
        NFoodCount = 0;
        board[y][x] = Sfood;
    } else {
        board[y][x] = Nfood;
    }
    tracker.EmptyCellRemoval(x, y);
}

//changeDirection
void GameController::changeDirection(Direction direction)
{
    Direction cur = snake.getDirection();
    if (direction == Direction::UP    && cur == Direction::DOWN)  return;
    if (direction == Direction::DOWN  && cur == Direction::UP)    return;
    if (direction == Direction::LEFT  && cur == Direction::RIGHT) return;
    if (direction == Direction::RIGHT && cur == Direction::LEFT)  return;
    snake.setDirection(direction);
}

//  willHitBoundary
bool GameController::willHitBoundary() const
{
    auto [x, y] = snake.getHead();
    int size = board.getSide();
    Direction dir = snake.getDirection();

    if (dir == Direction::UP    && y == 0)        return true;
    if (dir == Direction::DOWN  && y == size - 1) return true;
    if (dir == Direction::LEFT  && x == 0)        return true;
    if (dir == Direction::RIGHT && x == size - 1) return true;
    return false;
}

// eat
void GameController::eat(int growth)
{
    auto [nx, ny] = snake.getNextHead();
    tracker.EmptyCellRemoval(nx, ny);
    snake.grow(growth);
    board[ny][nx] = body;
    createFood();
}

// runStep
bool GameController::runStep()
{
    auto [nx, ny] = snake.getNextHead();
    int size = board.getSide();
    if (nx < 0 || nx >= size || ny < 0 || ny >= size)
        return false;

    if (willHitBoundary())
        return false;

    auto [tx, ty] = snake.getTail();
    CellContent nextCell = board[ny][nx];


    if (nextCell == body)    return false;
    if (nextCell == dropped) return false;

    if (nextCell == Nfood) {
        eat(1);
        emit foodEaten();
        m_stepsSinceDrop++;
        if (m_stepsSinceDrop >= m_dropInterval) { m_stepsSinceDrop = 0; dropTile(); }
        return true;
    }

    if (nextCell == Sfood) {
        eat(3);
        emit foodEaten();
        m_stepsSinceDrop++;
        if (m_stepsSinceDrop >= m_dropInterval) { m_stepsSinceDrop = 0; dropTile(); }
        return true;
    }

    tracker.EmptyCellRemoval(nx, ny);

    snake.move();
    board[ny][nx] = body;
    board[ty][tx] = empty;
    tracker.EmptyCellAddition(tx, ty);

    m_stepsSinceDrop++;
    if (m_stepsSinceDrop >= m_dropInterval) { m_stepsSinceDrop = 0; dropTile(); }

    return true;
}

int GameController::getScore() const
{
    return const_cast<Snake &>(snake).score();
}

std::pair<int,int> GameController::getHead()     const { return snake.getHead(); }
std::pair<int,int> GameController::getNextHead() const { return snake.getNextHead(); }
