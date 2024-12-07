#pragma once

#include <memory>
#include "Piece.h"

class Knight : public Piece {
public:
    Knight (ColorType color, Universe* universe, Vector xyzw);
    virtual ~Knight();

    std::vector<Vector> getValidMoves() const override;
    std::shared_ptr<Piece> clone() const override;
};

std::shared_ptr<Piece> createKnight(ColorType color, Universe* universe, Vector xyzw);

const std::vector<Vector> knightDirections = {
    Vector{1, 2, 0, 0},
    Vector{-1, 2, 0, 0},
    Vector{1, -2, 0, 0},
    Vector{-1, -2, 0, 0},
    Vector{2, 1, 0, 0},
    Vector{-2, 1, 0, 0},
    Vector{2, -1, 0, 0},
    Vector{-2, -1, 0, 0},

    Vector{1, 0, 4, 0},
    Vector{1, 0, -4, 0},
    Vector{-1, 0, 4, 0},
    Vector{-1, 0, -4, 0},
    Vector{2, 0, 2, 0},
    Vector{2, 0, -2, 0},
    Vector{-2, 0, 2, 0},
    Vector{-2, 0, -2, 0},

    Vector{0, 0, 2, 2},
    Vector{0, 0, -2, 2},
    Vector{0, 0, 2, -2},
    Vector{0, 0, -2, -2},
    Vector{0, 0, 4, 1},
    Vector{0, 0, -4, 1},
    Vector{0, 0, 4, -1},
    Vector{0, 0, -4, -1},

    Vector{0, 1, 4, 0},
    Vector{0, 1, -4, 0},
    Vector{0, -1, 4, 0},
    Vector{0, -1, -4, 0},
    Vector{0, 2, 2, 0},
    Vector{0, 2, -2, 0},
    Vector{0, -2, 2, 0},
    Vector{0, -2, -2, 0},

    Vector{0, 1, 0, 2},
    Vector{0, -1, 0, 2},
    Vector{0, 1, 0, -2},
    Vector{0, -1, 0, -2},
    Vector{0, 2, 0, 1},
    Vector{0, -2, 0, 1},
    Vector{0, 2, 0, -1},
    Vector{0, -2, 0, -1},

    Vector{0, 0, 2, 2},
    Vector{0, 0, -2, 2},
    Vector{0, 0, 2, -2},
    Vector{0, 0, -2, -2},
    Vector{0, 0, 4, 1},
    Vector{0, 0, -4, 1},
    Vector{0, 0, 4, -1},
    Vector{0, 0, -4, -1},
};
