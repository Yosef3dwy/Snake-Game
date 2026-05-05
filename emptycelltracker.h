#ifndef EMPTYCELLTRACKER_H
#define EMPTYCELLTRACKER_H

class EmptyCellTracker
{
private:
    std::vector<std::pair<int, int>> emptyCells;

    std::vector<std::vector<int>> cellIndices;

public:
    EmptyCellTracker(int side);

    void EmptyCellAddition(int x, int y);
    void EmptyCellRemoval(int x, int y);

    std::pair<int, int> getRandomEmptyCell();
};

#endif // EMPTYCELLTRACKER_H
