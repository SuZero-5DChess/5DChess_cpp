#include "Piece.h"

Piece::Piece(PieceType type, ColorType color, Universe* universe)
    : type_(type), color_(color), universe_(universe) {}

Piece::~Piece() {}

PieceType Piece::getType() const {
    return type_;
}

ColorType Piece::getColor() const {
    return color_;
}

std::string Piece::getSymbol() const {
    switch (type_) {
        case PieceType::Pawn: return color_ == ColorType::White ? "P" : "p";
        case PieceType::Rook: return color_ == ColorType::White ? "R" : "r";
        case PieceType::Knight: return color_ == ColorType::White ? "N" : "n";
        case PieceType::Bishop: return color_ == ColorType::White ? "B" : "b";
        case PieceType::Queen: return color_ == ColorType::White ? "Q" : "q";
        case PieceType::King: return color_ == ColorType::White ? "K" : "k";
        default: return " ";
    }
}

Vector Piece::getXYZW() const {
    return pos_xyzw_;
}
