#pragma once

#include "Universe.h"

class Game {
public:
    Game();
    ~Game();

    void initialize();

    void start();
    void handleMove(std::shared_ptr<Piece> piece, Vector dest);

    bool canNextTurn();

    std::vector<Vector> getMovablePieces();

    std::vector<Vector> readMove();
    bool getYesNo();

private:
    Universe universe_;
    ColorType currentPlayer_;

    void switchPlayer();
};
