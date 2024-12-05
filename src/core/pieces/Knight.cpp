#include "Knight.h"

#include <memory>
#include <Notfound.h>
#include <Universe.h>

Knight::Knight(ColorType color, Universe* universe)
    : Piece(PieceType::Rook, color, universe) {}

Knight::~Knight() {}

std::vector<Vector> Knight::getValidMoves() const {
    Vector pos = getXYZW();
    ColorType color = getColor();

    std::vector<Vector> directions = {
        Vector{1, 2, 0, 0},
        Vector{-1, 2, 0, 0},
        Vector{1, -2, 0, 0},
        Vector{-1, -2, 0, 0},
        Vector{2, 1, 0, 0},
        Vector{-2, 1, 0, 0},
        Vector{2, -1, 0, 0},
        Vector{-2, -1, 0, 0},

        Vector{1, 0, 2, 0},
        Vector{1, 0, -2, 0},
        Vector{-1, 0, 2, 0},
        Vector{-1, 0, -2, 0},
        Vector{2, 0, 1, 0},
        Vector{2, 0, -1, 0},
        Vector{-2, 0, 1, 0},
        Vector{-2, 0, -1, 0},

        Vector{0, 0, 1, 2},
        Vector{0, 0, -1, 2},
        Vector{0, 0, 1, -2},
        Vector{0, 0, -1, -2},
        Vector{0, 0, 2, 1},
        Vector{0, 0, -2, 1},
        Vector{0, 0, 2, -1},
        Vector{0, 0, -2, -1},

        Vector{0, 1, 2, 0},
        Vector{0, 1, -2, 0},
        Vector{0, -1, 2, 0},
        Vector{0, -1, -2, 0},
        Vector{0, 2, 1, 0},
        Vector{0, 2, -1, 0},
        Vector{0, -2, 1, 0},
        Vector{0, -2, -1, 0},

        Vector{0, 1, 0, 2},
        Vector{0, -1, 0, 2},
        Vector{0, 1, 0, -2},
        Vector{0, -1, 0, -2},
        Vector{0, 2, 0, 1},
        Vector{0, -2, 0, 1},
        Vector{0, 2, 0, -1},
        Vector{0, -2, 0, -1},

        Vector{0, 0, 1, 2},
        Vector{0, 0, -1, 2},
        Vector{0, 0, 1, -2},
        Vector{0, 0, -1, -2},
        Vector{0, 0, 2, 1},
        Vector{0, 0, -2, 1},
        Vector{0, 0, 2, -1},
        Vector{0, 0, -2, -1},
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

    return validMoves;
}
