#pragma once

#include <memory>
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(ColorType color, Universe* universe, Vector xyzw);
    virtual ~Queen();

    std::vector<Vector> getValidMoves() const override;
    std::shared_ptr<Piece> clone() const override;
};

std::shared_ptr<Piece> createQueen(ColorType color, Universe* universe, Vector xyzw);

const std::vector<Vector> queenDirections = {
    Vector{1, 0, 0, 0},
    Vector{-1, 0, 0, 0},
    Vector{0, 1, 0, 0},
    Vector{0, -1, 0, 0},
    Vector{0, 0, 2, 0},
    Vector{0, 0, -2, 0},
    Vector{0, 0, 0, 1},
    Vector{0, 0, 0, -1},

    Vector{1, 1, 0, 0},
    Vector{-1, 1, 0, 0},
    Vector{1, -1, 0, 0},
    Vector{-1, -1, 0, 0},

    Vector{1, 0, 2, 0},
    Vector{1, 0, -2, 0},
    Vector{-1, 0, 2, 0},
    Vector{-1, 0, -2, 0},

    Vector{0, 0, 2, 1},
    Vector{0, 0, -2, 1},
    Vector{0, 0, 2, -1},
    Vector{0, 0, -2, -1},

    Vector{0, 1, 2, 0},
    Vector{0, 1, -2, 0},
    Vector{0, -1, 2, 0},
    Vector{0, -1, -2, 0},

    Vector{0, 1, 0, 1},
    Vector{0, -1, 0, 1},
    Vector{0, 1, 0, -1},
    Vector{0, -1, 0, -1},

    Vector{0, 0, 2, 1},
    Vector{0, 0, -2, 1},
    Vector{0, 0, 2, -1},
    Vector{0, 0, -2, -1},


    Vector{1, 1, 2, 0},
    Vector{-1, 1, 2, 0},
    Vector{1, -1, 2, 0},
    Vector{-1, -1, 2, 0},
    Vector{1, 1, -2, 0},
    Vector{-1, 1, -2, 0},
    Vector{1, -1, -2, 0},
    Vector{-1, -1, -2, 0},

    Vector{1, 1, 0, 1},
    Vector{1, -1, 0, 1},
    Vector{1, 1, 0, -1},
    Vector{1, -1, 0, -1},
    Vector{-1, 1, 0, 1},
    Vector{-1, -1, 0, 1},
    Vector{-1, 1, 0, -1},
    Vector{-1, -1, 0, -1},

    Vector{1, 0, 2, 1},
    Vector{1, 0, -2, 1},
    Vector{1, 0, 2, -1},
    Vector{1, 0, -2, -1},
    Vector{-1, 0, 2, 1},
    Vector{-1, 0, -2, 1},
    Vector{-1, 0, 2, -1},
    Vector{-1, 0, -2, -1},

    Vector{0, 1, 2, 1},
    Vector{0, 1, -2, 1},
    Vector{0, 1, 2, -1},
    Vector{0, 1, -2, -1},
    Vector{0, -1, 2, 1},
    Vector{0, -1, -2, 1},
    Vector{0, -1, 2, -1},
    Vector{0, -1, -2, -1},


    Vector{1, 1, 2, 1},
    Vector{1, 1, -2, 1},
    Vector{1, 1, 2, -1},
    Vector{1, 1, -2, -1},
    Vector{1, -1, 2, 1},
    Vector{1, -1, -2, 1},
    Vector{1, -1, 2, -1},
    Vector{1, -1, -2, -1},
    Vector{-1, 1, 2, 1},
    Vector{-1, 1, -2, 1},
    Vector{-1, 1, 2, -1},
    Vector{-1, 1, -2, -1},
    Vector{-1, -1, 2, 1},
    Vector{-1, -1, -2, 1},
    Vector{-1, -1, 2, -1},
    Vector{-1, -1, -2, -1},
};
