#include "BeforePawn.h"

#include <Universe.h>

BeforePawn::BeforePawn(ColorType color, Universe* universe)
    : Piece(PieceType::Pawn, color, universe){}

BeforePawn::~BeforePawn() {}

std::vector<Vector> BeforePawn::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();
    int forward_up = color == ColorType::White ? 1 : -1;
    std::vector<Vector> entries = {
        Vector{0, -1 * forward_up, 0, 0},
        Vector{0, -2 * forward_up, 0, 0},
        Vector{0, 0, 0, -1 * forward_up},
        Vector{0, 0, 0, -2 * forward_up},
    };
    std::vector<Vector> validMoves;

    for (const auto& entry : entries) {
        Vector targetPos = pos + entry;

        if (universe_->getPiece(targetPos) == nullptr) {
            validMoves.push_back(targetPos);
        }
    }

    return validMoves;
}
