cmake_minimum_required(VERSION 3.10)

project(5DChessCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
        src/core/Board.cpp
        src/core/Piece.cpp
)

include_directories(
        src/core
        src/utils
)

add_executable(5DChessCPP ${SOURCE_FILES})