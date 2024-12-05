#include "Knight.h"

#include <memory>
#include <Notfound.h>
#include <Universe.h>

Knight::Knight(ColorType color, Universe* universe)
    : Piece(PieceType::Rook, color, universe) {}

Knight::~Knight() {}

void Knight::downdateDirection(Vector target) {
    removeValidMoves({target});
}

void Knight::updateDirection(Vector target) {
    appendValidMoves({target});
}


std::vector<Vector> Knight::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();

    std::vector<Vector> validMoves;

    for (const auto& direction: knightDirections) {
        Vector target = pos + direction;

        std::shared_ptr<Piece> piece = universe_->getPiece(target);
        if (piece == nullptr
            || (piece->getType() != PieceType::NotFound && piece->getColor() != color)) {
            validMoves.push_back(target);
        }
    }

    return validMoves;
}
