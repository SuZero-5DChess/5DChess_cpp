#pragma once

#include <sstream>

#include "Universe.h"

class Game {
public:
    Game();
    ~Game();

    void initialize();
    void initializeGame();

    void readAndExecuteMove();
    void processAndExecuteMove(const std::string& moveStr);

    void start();
    void handleMove(std::shared_ptr<Piece> piece, Vector dest);

    std::vector<Vector> getMovablePieces();

private:
    Universe universe_;
    ColorType currentPlayer_;
    int round_;

    std::vector<std::vector<Vector>> parsedMoves;
    size_t currentMoveIndex = 0;
    std::istringstream notationStream_;

    void switchPlayer();
};
