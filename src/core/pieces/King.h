#pragma once

#include <memory>

#include "Piece.h"

class King : public Piece {
public:
    King(ColorType color, Universe* universe, Vector xyzw);
    virtual ~King();

    std::vector<Vector> getValidMoves() const override;
    std::shared_ptr<Piece> clone() const override;

    void setIsMoved();
    bool getIsMoved() const;

private:
    bool isMoved_;
};

std::shared_ptr<Piece> createKing(ColorType color, Universe* universe, Vector xyzw);
