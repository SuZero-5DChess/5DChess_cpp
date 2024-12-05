#include "Board.h"
#include <iostream>
#include <Universe.h>

Board::Board(Universe* universe): universe_(universe) {
    grid_.resize(BOARD_SIZE, std::vector<std::shared_ptr<Piece>>(BOARD_SIZE, nullptr));
}

Board::~Board() {}

void Board::initialize() {
    // TODO: Initialize
}

std::shared_ptr<Piece> Board::getPiece(int x, int y) const {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        return grid_[x][y];
    }
    return universe_->returnNotFound();
}

void Board::setPiece(int x, int y, std::shared_ptr<Piece> piece) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        grid_[x][y] = piece;
    }
}

void Board::deletePiece(int x, int y) {
    grid_[x][y] = nullptr;
}


void Board::printBoard() const {
    for (int y = BOARD_SIZE - 1; y >= 0; --y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            auto piece = getPiece(x, y);
            if (piece) {
                std::cout << piece->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
