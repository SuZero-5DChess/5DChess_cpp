#pragma once

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(ColorType color, Universe* universe);
    virtual ~Queen();


    void downdateDirection(Vector start, Vector direction);
    void updateDirection(Vector start, Vector direction);
    virtual std::vector<Vector> getValidMoves() const override;
};

const std::vector<Vector> queenDirections = {
    Vector{1, 1, 0, 0},
    Vector{-1, 1, 0, 0},
    Vector{1, -1, 0, 0},
    Vector{-1, -1, 0, 0},

    Vector{1, 0, 1, 0},
    Vector{1, 0, -1, 0},
    Vector{-1, 0, 1, 0},
    Vector{-1, 0, -1, 0},

    Vector{0, 0, 1, 1},
    Vector{0, 0, -1, 1},
    Vector{0, 0, 1, -1},
    Vector{0, 0, -1, -1},

    Vector{0, 1, 1, 0},
    Vector{0, 1, -1, 0},
    Vector{0, -1, 1, 0},
    Vector{0, -1, -1, 0},

    Vector{0, 1, 0, 1},
    Vector{0, -1, 0, 1},
    Vector{0, 1, 0, -1},
    Vector{0, -1, 0, -1},

    Vector{0, 0, 1, 1},
    Vector{0, 0, -1, 1},
    Vector{0, 0, 1, -1},
    Vector{0, 0, -1, -1},


    Vector{1, 1, 1, 0},
    Vector{-1, 1, 1, 0},
    Vector{1, -1, 1, 0},
    Vector{-1, -1, 1, 0},
    Vector{1, 1, -1, 0},
    Vector{-1, 1, -1, 0},
    Vector{1, -1, -1, 0},
    Vector{-1, -1, -1, 0},

    Vector{1, 1, 0, 1},
    Vector{1, -1, 0, 1},
    Vector{1, 1, 0, -1},
    Vector{1, -1, 0, -1},
    Vector{-1, 1, 0, 1},
    Vector{-1, -1, 0, 1},
    Vector{-1, 1, 0, -1},
    Vector{-1, -1, 0, -1},

    Vector{1, 0, 1, 1},
    Vector{1, 0, -1, 1},
    Vector{1, 0, 1, -1},
    Vector{1, 0, -1, -1},
    Vector{-1, 0, 1, 1},
    Vector{-1, 0, -1, 1},
    Vector{-1, 0, 1, -1},
    Vector{-1, 0, -1, -1},

    Vector{0, 1, 1, 1},
    Vector{0, 1, -1, 1},
    Vector{0, 1, 1, -1},
    Vector{0, 1, -1, -1},
    Vector{0, -1, 1, 1},
    Vector{0, -1, -1, 1},
    Vector{0, -1, 1, -1},
    Vector{0, -1, -1, -1},


    Vector{1, 1, 1, 1},
    Vector{1, 1, -1, 1},
    Vector{1, 1, 1, -1},
    Vector{1, 1, -1, -1},
    Vector{1, -1, 1, 1},
    Vector{1, -1, -1, 1},
    Vector{1, -1, 1, -1},
    Vector{1, -1, -1, -1},
    Vector{-1, 1, 1, 1},
    Vector{-1, 1, -1, 1},
    Vector{-1, 1, 1, -1},
    Vector{-1, 1, -1, -1},
    Vector{-1, -1, 1, 1},
    Vector{-1, -1, -1, 1},
    Vector{-1, -1, 1, -1},
    Vector{-1, -1, -1, -1},
};
