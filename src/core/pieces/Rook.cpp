#include "Rook.h"

#include <memory>
#include <Notfound.h>
#include <Universe.h>

Rook::Rook(ColorType color, Universe* universe)
    : Piece(PieceType::Rook, color, universe), isMoved_(false) {}

Rook::~Rook() {}

std::vector<Vector> Rook::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();

    std::vector<Vector> directions = {
        Vector{1, 0, 0, 0},
        Vector{-1, 0, 0, 0},
        Vector{0, 1, 0, 0},
        Vector{0, -1, 0, 0},
        Vector{0, 0, 1, 0},
        Vector{0, 0, -1, 0},
        Vector{0, 0, 0, 1},
        Vector{0, 0, 0, -1},
    };
    std::vector<Vector> validMoves;

    for (const auto& direction: directions) {
        Vector current_target = pos + direction;

        while (true) {
            std::shared_ptr<Piece> piece = universe_->getPiece(current_target);
            if (piece == nullptr) {
                validMoves.push_back(current_target);
                current_target = current_target + direction;
            }
            else if (piece->getType() != PieceType::NotFound && piece->getColor() != color) {
                validMoves.push_back(current_target);
                break;
            }
            else {
                break;
            }
        }
    }

    return validMoves;
}

void Rook::setIsMoved() {
    isMoved_ = true;
}

bool Rook::getIsMoved() const {
    return isMoved_;
}

