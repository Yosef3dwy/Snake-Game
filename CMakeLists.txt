cmake_minimum_required(VERSION 3.16)
project(SnakeGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

qt_add_executable(SnakeGame
    MANUAL_FINALIZATION
    main.cpp
    mainwindow.cpp      mainwindow.h      mainwindow.ui
    settingmenu.cpp     settingmenu.h     settingmenu.ui
    start.cpp           start.h           start.ui
    gamewidget.cpp      gamewidget.h
    gamecontroller.cpp  gamecontroller.h
    snake.cpp           snake.h
    board.cpp           board.h
    emptycelltracker.cpp emptycelltracker.h


)

target_link_libraries(SnakeGame PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)

set_target_properties(SnakeGame PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(SnakeGame)
