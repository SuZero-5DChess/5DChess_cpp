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

std::ostream& operator<<(std::ostream& os, const ColorType& color) {
    switch (color) {
        case ColorType::White:
            os << "White";
            break;
        case ColorType::Black:
            os << "Black";
            break;
    }
    return os;
}

class Piece {
public:
    Piece(PieceType type, ColorType color, Universe* universe);
    virtual ~Piece();

    PieceType getType() const;
    ColorType getColor() const;
    std::string getSymbol() const;
    void setXYZW(Vector xyzw);
    Vector getXYZW() const;

    void setValidMoves(std::vector<Vector> validMoves);
    virtual std::vector<Vector> getValidMoves() const = 0;
    void appendValidMoves(std::vector<Vector> validMoves);
    void removeValidMoves(std::vector<Vector> validMoves);
    std::vector<Vector> readValidMoves() const;

protected:
    Universe* universe_;
    PieceType type_;
    ColorType color_;
    Vector pos_xyzw_;
    std::vector<Vector> validMoves_;
};
