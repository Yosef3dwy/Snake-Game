#include "board.h"

Board::Board(int size) : side(size)
{
    grid.assign(side, std::vector<CellContent>(side, CellContent::empty));
}

std::vector<CellContent>& Board::operator[](int index)
{
    return grid[index];
}

int Board::getSide() const { return side; }

void Board::initialize()
{
    grid.assign(side, std::vector<CellContent>(side, CellContent::empty));
}