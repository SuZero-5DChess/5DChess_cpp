#include "Notfound.h"

NotFound::NotFound(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::NotFound, color, universe, xyzw) {}

NotFound::~NotFound() {}

std::vector<Vector> NotFound::getValidMoves() const { return {Vector{-1, -1, -1, -1}}; }

std::shared_ptr<Piece> NotFound::clone() const {
    return nullptr;
}
