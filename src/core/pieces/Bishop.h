#pragma once

#include "Piece.h"

class Bishop: public Piece {
public:
    Bishop(ColorType color, Universe* universe);
    virtual ~Bishop();

    virtual std::vector<Vector> getValidMoves() const override;
};
