#pragma once

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(ColorType color, Universe* universe);
    virtual ~Rook();

    virtual std::vector<Vector> getValidMoves() const override;

    void setIsMoved();
    bool getIsMoved() const;

private:
    bool isMoved_;
};
