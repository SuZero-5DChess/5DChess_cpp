#pragma once

#include <string>
#include "Vector.h"

class Universe;

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    NotFound,
};

enum class ColorType {
    White,
    Black
};

class Piece {
public:
    Piece(PieceType type, ColorType color, Universe* universe);
    virtual ~Piece();

    PieceType getType() const;
    ColorType getColor() const;
    std::string getSymbol() const;
    Vector getXYZW() const;

    virtual std::vector<Vector> getValidMoves() const = 0;

protected:
    Universe* universe_;
    PieceType type_;
    ColorType color_;
    Vector pos_xyzw_;
};
