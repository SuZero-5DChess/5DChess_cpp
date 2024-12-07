#include "Queen.h"

#include <memory>
#include <algorithm>
#include <Notfound.h>
#include <Universe.h>

Queen::Queen(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::Queen, color, universe, xyzw){}

Queen::~Queen() {}

std::shared_ptr<Piece> createQueen(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<Queen>(color, universe, xyzw);
}

std::vector<Vector> Queen::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();
    std::vector<Vector> validMoves;
    std::vector<Vector> allCrossBlanks;

    for (const auto& direction: queenDirections) {
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
                    crossBlanks.push_back(Vector{current_target[2], current_target[3]});
                    current_target = current_target + direction;
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

std::shared_ptr<Piece> Queen::clone() const {
    return std::make_shared<Queen>(*this);
}
