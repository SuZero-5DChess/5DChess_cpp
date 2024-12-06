#include "Rook.h"

#include <memory>
#include <Notfound.h>
#include <Universe.h>

Rook::Rook(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::Rook, color, universe, xyzw), isMoved_(false) {}

Rook::~Rook() {}

std::shared_ptr<Piece> createRook(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<Rook>(color, universe, xyzw);
}

void Rook::downdateDirection(Vector start, Vector direction) {
    Vector pos = getXYZW();
    ColorType color = getColor();

    std::vector<Vector> validMoves;
    validMoves.push_back(start);

    bool isCrossBlank = false;
    Vector current_target = start + direction;

    while (true) {
        std::shared_ptr<Piece> piece = universe_->getPiece(current_target);
        if (piece == nullptr) {
            validMoves.push_back(current_target);
            current_target = current_target + direction;
            if (isCrossBlank) {
                universe_->addCrossBlankPiece(pos, Vector{current_target[2], current_target[3]});
            }
        }
        else if (piece->getType() != PieceType::NotFound && piece->getColor() != color) {
            validMoves.push_back(current_target);
            if (isCrossBlank) {
                universe_->addCrossBlankPiece(pos, Vector{current_target[2], current_target[3]});
            }
            break;
        }
        else {
            if (piece->getType() == PieceType::NotFound
                && direction[3] != 0
                && universe_->getTimeline(current_target[3]) != nullptr) {
                isCrossBlank = true;
            }
            else {
                break;
            }
        }
    }

    removeValidMoves(validMoves);
}

void Rook::updateDirection(Vector start, Vector direction) {
    Vector pos = getXYZW();
    ColorType color = getColor();

    std::vector<Vector> validMoves;
    validMoves.push_back(start);

    bool isCrossBlank = false;
    Vector current_target = start + direction;

    while (true) {
        std::shared_ptr<Piece> piece = universe_->getPiece(current_target);
        if (piece == nullptr) {
            validMoves.push_back(current_target);
            current_target = current_target + direction;
            if (isCrossBlank) {
                universe_->addCrossBlankPiece(pos, Vector{current_target[2], current_target[3]});
            }
        }
        else if (piece->getType() != PieceType::NotFound && piece->getColor() != color) {
            validMoves.push_back(current_target);
            if (isCrossBlank) {
                universe_->addCrossBlankPiece(pos, Vector{current_target[2], current_target[3]});
            }
            break;
        }
        else {
            if (piece->getType() == PieceType::NotFound
                && direction[3] != 0
                && universe_->getTimeline(current_target[3]) != nullptr) {
                isCrossBlank = true;
            }
            else {
                break;
            }
        }
    }

    appendValidMoves(validMoves);
}


std::vector<Vector> Rook::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();
    std::vector<Vector> validMoves;

    for (const Vector& direction: rookDirections) {
        bool isCrossBlank = false;
        Vector current_target = pos + direction;

        while (true) {
            std::shared_ptr<Piece> piece = universe_->getPiece(current_target);
            if (piece == nullptr) {
                validMoves.push_back(current_target);
                current_target = current_target + direction;
                if (isCrossBlank) {
                    universe_->addCrossBlankPiece(pos, Vector{current_target[2], current_target[3]});
                }
            }
            else if (piece->getType() != PieceType::NotFound && piece->getColor() != color) {
                validMoves.push_back(current_target);
                if (isCrossBlank) {
                    universe_->addCrossBlankPiece(pos, Vector{current_target[2], current_target[3]});
                }
                break;
            }
            else {
                if (piece->getType() == PieceType::NotFound
                    && direction[3] != 0
                    && universe_->getTimeline(current_target[3]) != nullptr) {
                    isCrossBlank = true;
                }
                else {
                    break;
                }
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

