cmake_minimum_required(VERSION 3.26)
project(minesweeper)
include_directories("C:/Libraries/SFML-2.5.1/include")
set(CMAKE_CXX_STANDARD 17)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(minesweeper minesweeper.cpp
        Toolbox.h
        Toolbox.cpp
        Button.h
        Button.cpp
        Tile.cpp
        Tile.h
        GameState.h
        GameState.cpp
        minesweeper.h
        Mine.h
        Mine.cpp)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
