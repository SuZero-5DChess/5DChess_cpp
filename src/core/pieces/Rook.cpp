#include "Rook.h"

#include <memory>
#include <algorithm>
#include <Notfound.h>
#include <Universe.h>

Rook::Rook(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::Rook, color, universe, xyzw), isMoved_(false) {}

Rook::~Rook() {}

std::shared_ptr<Piece> createRook(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<Rook>(color, universe, xyzw);
}

std::vector<Vector> Rook::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();
    std::vector<Vector> validMoves;
    std::vector<Vector> allCrossBlanks;

    for (const Vector& direction: rookDirections) {
        std::vector<Vector> crossBlanks;
        Vector current_target = pos + direction;

        while (true) {
            std::shared_ptr<Piece> piece = universe_->getPiece(current_target);
            if (piece == nullptr) {
                validMoves.push_back(current_target - pos);
                if (! crossBlanks.empty()) {
                    for (auto cross_blank : crossBlanks) {
                        if (std::find(allCrossBlanks.begin(), allCrossBlanks.end(), cross_blank) == allCrossBlanks.end()) {
                            allCrossBlanks.push_back(cross_blank);
                        }
                    }
                    crossBlanks.clear();
                }
                current_target = current_target + direction;
            }
            else if (piece->getType() != PieceType::NotFound && piece->getColor() != color) {
                validMoves.push_back(current_target - pos);
                if (! crossBlanks.empty()) {
                    for (auto cross_blank : crossBlanks) {
                        if (std::find(allCrossBlanks.begin(), allCrossBlanks.end(), cross_blank) == allCrossBlanks.end()) {
                            allCrossBlanks.push_back(cross_blank);
                        }
                    }
                    crossBlanks.clear();
                }
                break;
            }
            else {
                if (piece->getType() == PieceType::NotFound
                    && direction[3] != 0
                    && universe_->getTimeline(current_target[3]) != nullptr
                    && universe_->getTimeline(current_target[3])->getLength() < current_target[2] + 1) {
                    current_target = current_target + direction;
                    crossBlanks.push_back(Vector{current_target[2], current_target[3]});
                }
                else {
                    break;
                }
            }
        }
    }

    for (auto cross_blank : allCrossBlanks) {
        universe_->addCrossBlankPiece(pos, cross_blank);
    }

    return validMoves;
}

std::shared_ptr<Piece> Rook::clone() const {
    return std::make_shared<Rook>(*this);
}


void Rook::setIsMoved() {
    isMoved_ = true;
}

bool Rook::getIsMoved() const {
    return isMoved_;
}

