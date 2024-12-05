#pragma once

#include <string>

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum class ColorType {
    White,
    Black
};

class Piece {
public:
    Piece(PieceType type, ColorType color);
    virtual ~Piece();

    PieceType getType() const;
    ColorType getColor() const;
    std::string getSymbol() const;

    virtual bool isValidMove(/* TODO: params */) const = 0;

protected:
    PieceType type_;
    ColorType color_;
};
