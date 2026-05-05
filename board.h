#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    std::vector<std::vector<int>> grid;
    int side;

public:
    Board(int size);
    std::vector<CellContent>& operator[](int index);
    int getSide();
    void initialize();
    void render();
};

#endif // BOARD_H
