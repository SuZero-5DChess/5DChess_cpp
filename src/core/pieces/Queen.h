#pragma once

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(ColorType color, Universe* universe);
    virtual ~Queen();

    virtual std::vector<Vector> getValidMoves() const override;
};
