#pragma once

#include <memory>

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(ColorType color, Universe* universe, Vector xyzw);
    virtual ~Rook();


    void downdateDirection(Vector start, Vector direction);
    void updateDirection(Vector start, Vector direction);
    virtual std::vector<Vector> getValidMoves() const override;

    void setIsMoved();
    bool getIsMoved() const;

private:
    bool isMoved_;
};

std::shared_ptr<Piece> createRook(ColorType color, Universe* universe, Vector xyzw);

const std::vector<Vector> rookDirections = {
    Vector{1, 0, 0, 0},
    Vector{-1, 0, 0, 0},
    Vector{0, 1, 0, 0},
    Vector{0, -1, 0, 0},
    Vector{0, 0, 2, 0},
    Vector{0, 0, -2, 0},
    Vector{0, 0, 0, 1},
    Vector{0, 0, 0, -1},
};