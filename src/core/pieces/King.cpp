#include "King.h"

#include <memory>
#include <Notfound.h>
#include <Queen.h>
#include <Rook.h>
#include <Universe.h>

King::King(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::King, color, universe, xyzw){}

King::~King() {}

std::shared_ptr<Piece> createKing(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<King>(color, universe, xyzw);
}

std::vector<Vector> King::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();
    std::vector<Vector> validMoves;

    for (const auto& direction: queenDirections) {
        Vector target = pos + direction;

        std::shared_ptr<Piece> piece = universe_->getPiece(target);
        if (piece == nullptr
            || (piece->getType() != PieceType::NotFound && piece->getColor() != color)) {
            validMoves.push_back(direction);
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
                    Vector{-2, 0, 0, 0}
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
                    Vector{2, 0, 0, 0}
                );
            }
        }
    }

    return validMoves;
}

std::shared_ptr<Piece> King::clone() const {
    return std::make_shared<King>(*this);
}


void King::setIsMoved() {
    isMoved_ = true;
}

bool King::getIsMoved() const {
    return isMoved_;
}

