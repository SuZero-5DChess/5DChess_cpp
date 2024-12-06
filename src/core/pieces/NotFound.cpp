#include "Notfound.h"

NotFound::NotFound(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::NotFound, color, universe, xyzw) {}

NotFound::~NotFound() {}

std::vector<Vector> NotFound::getValidMoves() const { return {Vector{-1, -1, -1, -1}}; }
