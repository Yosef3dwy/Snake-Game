#include "board.h"
#include <vector>

Board::Board(int size)
{
    side = size;
    grid = std::vector<std::vector<CellContent>>(side, std::vector<CellContent>(side, CellContent::empty));
}

std::vector<CellContent>& Board::operator[](int index)
{
    return grid[index];
}

int Board::getSide() const   // FIX: added const
{
    return side;
}

void Board::initialize()
{
    grid = std::vector<std::vector<CellContent>>(side, std::vector<CellContent>(side, CellContent::empty));
}