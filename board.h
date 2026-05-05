#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "enums.h"

class Board {
private:
    std::vector<std::vector<CellContent>> grid;
    int side;

public:
    Board(int size);
    int getSide() const;   // FIX: must be const to match const usage
    void initialize();
    std::vector<CellContent>& operator[](int index);
};

#endif