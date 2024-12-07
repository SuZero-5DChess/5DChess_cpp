#pragma once

#include <memory>
#include "Piece.h"

class AfterPawn : public Piece {
public:
    AfterPawn(ColorType color, Universe* universe, Vector xyzw);
    virtual ~AfterPawn();

    std::vector<Vector> getValidMoves() const override;
    std::shared_ptr<Piece> clone() const override;

};

std::shared_ptr<Piece> createAfterPawn(ColorType color, Universe* universe, Vector xyzw);
