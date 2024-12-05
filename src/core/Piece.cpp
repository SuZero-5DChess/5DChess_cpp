#include "Piece.h"

Piece::Piece(PieceType type, ColorType color)
    : type_(type), color_(color) {}

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
