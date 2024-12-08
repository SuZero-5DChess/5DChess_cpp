#include "AfterPawn.h"

#include <Universe.h>

AfterPawn::AfterPawn(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::AfterPawn, color, universe, xyzw) {}

AfterPawn::~AfterPawn() {}

std::shared_ptr<Piece> createAfterPawn(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<AfterPawn>(color, universe, xyzw);
}

std::vector<Vector> AfterPawn::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();
    int forward_up = color == ColorType::White ? 1 : -1;

    // no take

    std::vector<Vector> entries = {
        Vector{0, -1 * forward_up, 0, 0},
        Vector{0, 0, 0, -1 * forward_up},
    };
    std::vector<Vector> validMoves;

    for (const auto& entry : entries) {
        Vector targetPos = pos + entry;

        if (universe_->getPiece(targetPos) == nullptr) {
            validMoves.push_back(entry);
        }
    }

    // take

    std::shared_ptr<Piece> right_now_dest = universe_->getPiece(pos + Vector{1, 0, 0, 0});
    std::shared_ptr<Piece> right_now_orig = universe_->getPiece(pos + Vector{1, -2 * forward_up, 0, 0});
    std::shared_ptr<Piece> right_past_dest = universe_->getPiece(pos + Vector{1, 0, -2, 0});
    std::shared_ptr<Piece> right_past_orig = universe_->getPiece(pos + Vector{1, -2 * forward_up, -2, 0});

    std::shared_ptr<Piece> left_now_dest = universe_->getPiece(pos + Vector{-1, 0, 0, 0});
    std::shared_ptr<Piece> left_now_orig = universe_->getPiece(pos + Vector{-1, -2 * forward_up, 0, 0});
    std::shared_ptr<Piece> left_past_dest = universe_->getPiece(pos + Vector{-1, 0, -2, 0});
    std::shared_ptr<Piece> left_past_orig = universe_->getPiece(pos + Vector{-1, -2 * forward_up, -2, 0});

    if (right_now_dest && right_past_dest
        && right_now_dest->getType() == PieceType::AfterPawn
        && right_now_dest->getColor() != color
        && right_now_orig == nullptr
        && right_past_dest == nullptr
        && right_past_orig-> getType() == PieceType::AfterPawn && right_past_orig->getColor() != color) {
        validMoves.push_back(Vector{1, -1 * forward_up, 0, 0});
    }

    if (left_now_dest && left_past_dest
        && left_now_dest->getType() == PieceType::AfterPawn
        && left_now_dest->getColor() != color
        && left_now_orig == nullptr
        && left_past_dest == nullptr
        && left_past_orig-> getType() == PieceType::AfterPawn
        && left_past_orig->getColor() != color) {
        validMoves.push_back(Vector{-1, -1 * forward_up, 0, 0});
    }

    std::vector<Vector> take_entries = {
        Vector{1, -1 * forward_up, 0, 0},
        Vector{-1, -1 * forward_up, 0, 0},
        Vector{0, 0, 2, -1 * forward_up},
        Vector{0, 0, -2, -1 * forward_up},
    };

    for (const auto& entry: take_entries) {
        Vector targetPos = pos + entry;
        std::shared_ptr<Piece> targetPiece = universe_->getPiece(targetPos);
        if (targetPiece != nullptr && targetPiece->getColor() != color) {
            validMoves.push_back(entry);
        }
    }

    return validMoves;
}

std::shared_ptr<Piece> AfterPawn::clone() const {
    return std::make_shared<AfterPawn>(*this);
}
