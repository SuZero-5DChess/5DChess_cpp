#include "Bishop.h"

#include <memory>
#include <algorithm>
#include <Notfound.h>
#include <Universe.h>

Bishop::Bishop(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::Bishop, color, universe, xyzw){}

Bishop::~Bishop() {}

std::shared_ptr<Piece> createBishop(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<Bishop>(color, universe, xyzw);
}

std::vector<Vector> Bishop::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();
    std::vector<Vector> validMoves;

    for (const auto& direction: bishopDirections) {
        Vector current_target = pos + direction;

        while (true) {
            std::shared_ptr<Piece> piece = universe_->getPiece(current_target);
            if (piece == nullptr) {
                validMoves.push_back(current_target - pos);
                current_target = current_target + direction;
            }
            else if (piece->getType() != PieceType::NotFound && piece->getColor() != color) {
                validMoves.push_back(current_target - pos);
                break;
            }
            else {
                if (piece->getType() == PieceType::NotFound
                    && direction[3] != 0
                    && universe_->getTimeline(current_target[3]) != nullptr
                    && universe_->getTimeline(current_target[3])->getLength() < current_target[2] + 1) {
                    current_target = current_target + direction;
                }
                else {
                    break;
                }
            }
        }
    }

    return validMoves;
}

std::shared_ptr<Piece> Bishop::clone() const {
    return std::make_shared<Bishop>(*this);
}
