#pragma once

#include "Universe.h"

class Game {
public:
    Game();
    ~Game();

    void start();

    void handleMove(/* TODO: params */);

    void checkGameState();

private:
    Universe universe_;

    ColorType currentPlayer_;

    void switchPlayer();
};
