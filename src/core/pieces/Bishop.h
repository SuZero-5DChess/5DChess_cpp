#pragma once

#include <memory>

#include "Piece.h"

class Bishop: public Piece {
public:
    Bishop(ColorType color, Universe* universe, Vector xyzw);
    virtual ~Bishop();

    void downdateDirection(Vector start, Vector direction);
    void updateDirection(Vector start, Vector direction);
    virtual std::vector<Vector> getValidMoves() const override;
};

std::shared_ptr<Piece> createBishop(ColorType color, Universe* universe, Vector xyzw);

const std::vector<Vector> bishopDirections = {
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
};