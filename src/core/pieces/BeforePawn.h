#pragma once

#include "Piece.h"

class BeforePawn : public Piece {
public:
    BeforePawn(ColorType color, Universe* universe);
    virtual ~BeforePawn();

    virtual std::vector<Vector> getValidMoves() const override;
};
