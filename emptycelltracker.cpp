#include <vector>
#include <utility>
#include <stdexcept>
#include <cstdlib>

#include "emptycelltracker.h"


EmptyCellTracker::EmptyCellTracker(int side) 
{
        cellIndices.assign(side, std::vector<int>(side, -1));

        for (int y = 0; y < side; ++y) {
            for (int x = 0; x < side; ++x) {
                EmptyCellAddition(x, y);
            }
        }
    }


void EmptyCellTracker::EmptyCellAddition(int x, int y) {
    if (cellIndices[y][x] != -1) return; // Already marked as empty

    emptyCells.push_back({x, y});

    cellIndices[y][x] = emptyCells.size() - 1;
}

void EmptyCellTracker::EmptyCellRemoval(int x, int y) 
{
    int indexToRemove = cellIndices[y][x];
    if (indexToRemove == -1) return;

    std::pair<int, int> lastCell = emptyCells.back();

    emptyCells[indexToRemove] = lastCell;

    cellIndices[lastCell.second][lastCell.first] = indexToRemove;

    emptyCells.pop_back();

    cellIndices[y][x] = -1;
}

std::pair<int, int> EmptyCellTracker::getRandomEmptyCell() {
        if (emptyCells.empty()) {
            throw std::runtime_error("No empty cells available!");
        }

        int randomIndex = std::rand() % emptyCells.size();
        return emptyCells[randomIndex];
    }