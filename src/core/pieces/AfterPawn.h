#pragma once

#include "Piece.h"

class AfterPawn : public Piece {
public:
    AfterPawn(ColorType color, Universe* universe);
    virtual ~AfterPawn();

    virtual std::vector<Vector> getValidMoves() const override;

};
