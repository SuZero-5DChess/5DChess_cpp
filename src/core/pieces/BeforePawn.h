#pragma once

#include <memory>

#include "Piece.h"

class BeforePawn : public Piece {
public:
    BeforePawn(ColorType color, Universe* universe, Vector xyzw);
    virtual ~BeforePawn();

    virtual std::vector<Vector> getValidMoves() const override;
};

std::shared_ptr<Piece> createBeforePawn(ColorType color, Universe* universe, Vector xyzw);
