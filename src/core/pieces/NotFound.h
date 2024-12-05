#pragma once

#include "Piece.h"

class NotFound : public Piece {
public:
    NotFound(ColorType color, Universe* universe);
    virtual ~NotFound();

    virtual std::vector<Vector> getValidMoves() const override;
};
