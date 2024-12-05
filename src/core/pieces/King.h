#pragma once

#include "Piece.h"

class King : public Piece {
public:
    King(ColorType color, Universe* universe);
    virtual ~King();

    virtual std::vector<Vector> getValidMoves() const override;

    void setIsMoved();
    bool getIsMoved() const;

private:
    bool isMoved_;
};
