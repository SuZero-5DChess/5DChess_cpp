#include "Queen.h"

#include <memory>
#include <Notfound.h>
#include <Universe.h>

Queen::Queen(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::Queen, color, universe, xyzw){}

Queen::~Queen() {}

std::shared_ptr<Piece> createQueen(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<Queen>(color, universe, xyzw);
}

void Queen::downdateDirection(Vector start, Vector direction) {
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

void Queen::updateDirection(Vector start, Vector direction) {
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


std::vector<Vector> Queen::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();

    std::vector<Vector> validMoves;

    for (const auto& direction: queenDirections) {
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
