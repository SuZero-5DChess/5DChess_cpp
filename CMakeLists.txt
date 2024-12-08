cmake_minimum_required(VERSION 3.10)

project(5DChessCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
        src/core/pieces/NotFound.cpp
        src/core/pieces/AfterPawn.cpp
        src/core/pieces/BeforePawn.cpp
        src/core/pieces/Rook.cpp
        src/core/pieces/Bishop.cpp
        src/core/pieces/Knight.cpp
        src/core/pieces/Queen.cpp
        src/core/pieces/King.cpp

        src/core/Board.cpp
        src/core/Piece.cpp
        src/core/Timeline.cpp
        src/core/Universe.cpp
        src/game/Game.cpp

        src/Main.cpp

        src/utils/Vector.cpp
        src/utils/Parser.cpp
)

include_directories(
        src/core
        src/core/pieces
        src/game
        src/utils
)

add_executable(5DChessCPP ${SOURCE_FILES})