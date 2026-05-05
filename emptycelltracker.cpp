#include "emptycelltracker.h"

#include <vector>
#include <utility>
#include <stdexcept>
#include <cstdlib>

class EmptyCellTracker {
private:
    // Stores the actual empty coordinates for fast random picking
    std::vector<std::pair<int, int>> emptyCells;

    // Maps board[y][x] to its index in emptyCells.
    // Stores -1 if the cell is currently occupied (not in the vector).
    std::vector<std::vector<int>> cellIndices;

public:
    EmptyCellTracker(int rows, int cols) {
        // Initialize the tracking map with -1
        cellIndices.assign(rows, std::vector<int>(cols, -1));

        // Initially, all cells are empty
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                addCell(x, y);
            }
        }
    }

    // O(1) Addition: Occurs when the snake tail leaves a cell
    void addCell(int x, int y) {
        if (cellIndices[y][x] != -1) return; // Already marked as empty

        // 1. Add the new coordinate to the end of the vector
        emptyCells.push_back({x, y});

        // 2. Record its index in the 2D map
        cellIndices[y][x] = emptyCells.size() - 1;
    }

    // O(1) Removal: Occurs when the snake head enters a cell or food is spawned
    void removeCell(int x, int y) {
        int indexToRemove = cellIndices[y][x];
        if (indexToRemove == -1) return; // Already not empty

        // 1. Get the coordinate of the LAST element in the vector
        std::pair<int, int> lastCell = emptyCells.back();

        // 2. Overwrite the element we want to remove with the last element
        emptyCells[indexToRemove] = lastCell;

        // 3. Update the 2D map so the last element knows its new index
        cellIndices[lastCell.second][lastCell.first] = indexToRemove;

        // 4. Remove the duplicate from the end of the vector
        emptyCells.pop_back();

        // 5. Mark the removed cell as -1 in the map
        cellIndices[y][x] = -1;
    }

    // O(1) Random Generation
    std::pair<int, int> getRandomEmptyCell() {
        if (emptyCells.empty()) {
            throw std::runtime_error("No empty cells available!"); // You won the game!
        }

        int randomIndex = std::rand() % emptyCells.size();
        return emptyCells[randomIndex];
    }
};
