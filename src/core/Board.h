#pragma once

#include <vector>
#include <memory>
#include "Piece.h"

class Universe;
const int BOARD_SIZE = 8;

class Board {
public:
    Board(Universe* universe);
    ~Board();

    void initialize();

    std::shared_ptr<Piece> getPiece(int x, int y) const;
    void setPiece(int x, int y, std::shared_ptr<Piece> piece);
    void deletePiece(int x, int y);

    void printBoard() const;

private:
    Universe* universe_;
    std::vector<std::vector<std::shared_ptr<Piece>>> grid_;
    Vector pos_zw;
};
