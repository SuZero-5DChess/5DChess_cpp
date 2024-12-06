#include "Knight.h"

#include <memory>
#include <Notfound.h>
#include <Universe.h>

Knight::Knight(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::Knight, color, universe, xyzw) {}

Knight::~Knight() {}

std::shared_ptr<Piece> createKnight(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<Knight>(color, universe, xyzw);
}

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
