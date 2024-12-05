#include "King.h"

#include <memory>
#include <Notfound.h>
#include <Rook.h>
#include <Universe.h>

King::King(ColorType color, Universe* universe)
    : Piece(PieceType::Rook, color, universe){}

King::~King() {}

std::vector<Vector> King::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();

    std::vector<Vector> directions = {
        Vector{1, 1, 0, 0},
        Vector{-1, 1, 0, 0},
        Vector{1, -1, 0, 0},
        Vector{-1, -1, 0, 0},

        Vector{1, 0, 1, 0},
        Vector{1, 0, -1, 0},
        Vector{-1, 0, 1, 0},
        Vector{-1, 0, -1, 0},

        Vector{0, 0, 1, 1},
        Vector{0, 0, -1, 1},
        Vector{0, 0, 1, -1},
        Vector{0, 0, -1, -1},

        Vector{0, 1, 1, 0},
        Vector{0, 1, -1, 0},
        Vector{0, -1, 1, 0},
        Vector{0, -1, -1, 0},

        Vector{0, 1, 0, 1},
        Vector{0, -1, 0, 1},
        Vector{0, 1, 0, -1},
        Vector{0, -1, 0, -1},

        Vector{0, 0, 1, 1},
        Vector{0, 0, -1, 1},
        Vector{0, 0, 1, -1},
        Vector{0, 0, -1, -1},
    };
    std::vector<Vector> validMoves;

    for (const auto& direction: directions) {
        Vector target = pos + direction;

        std::shared_ptr<Piece> piece = universe_->getPiece(target);
        if (piece == nullptr
            || (piece->getType() != PieceType::NotFound && piece->getColor() != color)) {
            validMoves.push_back(target);
        }
    }

    // castle

    if (isMoved_) return validMoves;

    int z = pos[2];
    int w = pos[3];

    std::shared_ptr<Piece> rook1 = universe_->getPiece(
        Vector{0, color == ColorType::White ? 7 : 0, z, w}
    );
    if (rook1->getType() == PieceType::Rook) {
        if (typeid(*rook1) != typeid(Rook)) {
            Rook* rookPtr = static_cast<Rook*>(rook1.get());
            bool isMoved = rookPtr->getIsMoved();
            if (!isMoved) {
                validMoves.push_back(
                    Vector{2, color == ColorType::White ? 7 : 0, z, w}
                );
            }
        }
    }

    std::shared_ptr<Piece> rook2 = universe_->getPiece(
        Vector{7, color == ColorType::White ? 7 : 0, z, w}
    );
    if (rook2->getType() == PieceType::Rook) {
        if (typeid(*rook2) != typeid(Rook)) {
            Rook* rookPtr = static_cast<Rook*>(rook2.get());
            bool isMoved = rookPtr->getIsMoved();
            if (!isMoved) {
                validMoves.push_back(
                    Vector{6, color == ColorType::White ? 7 : 0, z, w}
                );
            }
        }
    }

    return validMoves;
}

void King::setIsMoved() {
    isMoved_ = true;
}

bool King::getIsMoved() const {
    return isMoved_;
}

