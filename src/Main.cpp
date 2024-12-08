#include <iostream>
#include <chrono>
#include "Game.h"

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    Game game;
    game.start();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Game runtime: " << duration.count() << " ms" << std::endl;

    return 0;
}
