#pragma once

#include "Piece.h"

class NotFound : public Piece {
public:
    NotFound(ColorType color, Universe* universe, Vector xyzw);
    virtual ~NotFound();

    virtual std::vector<Vector> getValidMoves() const override;
    std::shared_ptr<Piece> clone() const override;
};
