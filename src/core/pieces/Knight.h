#pragma once

#include "Piece.h"

class Knight : public Piece {
public:
    Knight (ColorType color, Universe* universe);
    virtual ~Knight();

    virtual std::vector<Vector> getValidMoves() const override;
};
