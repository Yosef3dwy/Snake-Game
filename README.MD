# Snake Game — Qt C++

---

##  Group Members
| Name | ID |
|------|----|
| Youssef Mohamed Ahmed Eladawy | 2300578 |
| Kevin Hany Beshara            | 2300381 |
| ibrahim alaa ibrahim          | 2300075 |


---

## Project Description

A fully featured Snake game built with **C++ and the Qt framework**. The player controls a snake on a grid, eating food to grow longer and increase their score. The game includes multiple difficulty levels, grid size options, special food types, a tile-dropping hazard mechanic, sound effects, background music, and a settings menu.

---

## Selected Data Structures & Justification

### `std::deque<std::pair<int,int>>` - Snake Body
Used in `snake.cpp` to store the snake's body segments. A deque allows **O(1) insertion at the front** (new head) and **O(1) removal at the back** (old tail), which is exactly the operation pattern of a moving snake. A vector would require shifting all elements on every move.

### `std::vector<std::vector<CellContent>>` - Game Board Grid
Used in `board.cpp` as a 2D grid representing every cell's state (empty, body, food, dropped tile). Provides **O(1) random access** by `[row][col]`, which is essential for changing the state of the cells (empty, body, Nfood, Sfood, dropped).

### `std::vector<std::pair<int,int>>` - Empty Cell List (EmptyCellTracker)
Used in `emptycelltracker.cpp` to maintain a flat list of all empty cells for **O(1) random food/tile placement**. A naive approach would scan the entire board each time food spawns.

### `std::vector<std::vector<int>>` - Cell Index Map (EmptyCellTracker)
A parallel 2D array that maps each grid coordinate to its index in the empty cell list. This enables **O(1) removal** of a specific cell from the flat list using a swap-with-last strategy, avoiding expensive searches.

---

## Implemented Features

- Classic snake movement with arrow keys or WASD
- Pause / resume with `P`
- Two food types:
  - **Normal food** - grows snake by 1
  - **Super food** - grows snake by 3 (appears every 5 normal foods)
- **Drop Tiles** mode - random obstacle tiles fall onto the board over time
- Three difficulty levels - Easy, Medium, Hard (affects speed and drop rate)
- Three grid sizes - 15x15, 20x20, 25x25

---

## How to Compile and Run

### Requirements
- Qt 6.x (with Qt Multimedia module)
- A C++17-compatible compiler (GCC, MSVC, or Clang)
- Qt Creator

---

### Qt Creator

1. remove the `build` folder from the project if existed.
2. Open **Qt Creator**.
3. Go to **File --> Open File or Project**.
4. Select the `CMakeLists.txt` project file.
5. Click **Configure Project**.
6. Click the **build** button.
7. Put the **Asset Files** in the same `build` directory.
8. Return to **Qt Creator** and click the green **run** button.


---

### Required Asset Files

Make sure these files are in the **same directory as the executable**:

| File | Purpose |
|------|---------|
| `BG.png` | Main menu background image |
| `BG_music.mp3` | Background music |
| `eat.wav` | Food eaten sound effect |

---

## AI Usage Declaration

**1. Debugging logic errors**
AI helped identify and fix a bug where the snake's head would jump an extra cell forward when eating a superfood. The root cause was that `grow()` was advancing the head position internally, which conflicted with the head movement already handled by `runStep()`.

**2. Data structure selection for random empty-cell placement**
We had a theoretical solution for placing food on a random empty cell: instead of generating a random index and checking if it is occupied, we would pass the generator a container that holds only the currently empty cells, guaranteeing any pick is valid. We knew the direction but needed guidance on the best data structure to back it. AI recommended combining a flat `std::vector<std::pair<int,int>>` of empty cells (for O(1) random access by index) with a parallel 2D index map (for O(1) removal using a swap-with-last strategy). This became the `EmptyCellTracker` class.

**3. Qt framework guidance**
AI helped us understand Qt concepts that were new to us, including how signals and slots work, how to connect widgets to game logic, how the event loop drives the game timer, and how `QPainter` is used for custom rendering.

**4. Backend guidance**
AI assisted in brainstorming the design of the `GameController` class, particularly how to cleanly centralize all state changes - movement, eating, growing, and tile dropping - through a single `runStep()` function. It also helped think through how to handle pending snake growth using a simple counter (`m_pendingGrowth`) rather than modifying the snake's data structure directly.

---

## Project Structure

```
snake-project/
- main.cpp              # Entry point
- mainwindow.cpp/h      # Main menu window
- start.cpp/h           # Game session wrapper (score, restart, menu)
- gamewidget.cpp/h      # Qt widget — rendering & input handling
- gamecontroller.cpp/h  # Core game logic (step, eat, drop)
- snake.cpp/h           # Snake data structure & movement
- board.cpp/h           # 2D grid board
- emptycelltracker.cpp/h# Efficient empty cell tracking
- food.cpp/h            # Food type definitions
- enums.cpp/h           # Shared enums (Direction, CellContent)
- settingmenu.cpp/h     # Settings UI
- BG.png                # Background image asset
- BG_music.mp3          # Background music asset
- eat.wav               # Sound effect asset
```