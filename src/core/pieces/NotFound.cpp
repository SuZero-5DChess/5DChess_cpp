#include "Notfound.h"

NotFound::NotFound(ColorType color, Universe* universe)
    : Piece(PieceType::NotFound, color, universe) {}

NotFound::~NotFound() {}

std::vector<Vector> NotFound::getValidMoves() const { return {Vector{-1, -1, -1, -1}}; }
