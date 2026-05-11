#ifndef EMPTYCELLTRACKER_H
#define EMPTYCELLTRACKER_H

#include <vector>
#include <utility>

class EmptyCellTracker
{
private:
    std::vector<std::pair<int, int>> emptyCells;
    std::vector<std::vector<int>>    cellIndices;

public:
    EmptyCellTracker(int side);

    void EmptyCellAddition(int x, int y);
    void EmptyCellRemoval(int x, int y);

    std::pair<int, int> getRandomEmptyCell();
    bool isEmpty() const;
};

#endif // EMPTYCELLTRACKER_H
