#include "BeforePawn.h"

#include <AfterPawn.h>
#include <Notfound.h>
#include <Universe.h>

BeforePawn::BeforePawn(ColorType color, Universe* universe, Vector xyzw)
    : Piece(PieceType::BeforePawn, color, universe, xyzw){}

BeforePawn::~BeforePawn() {}

std::shared_ptr<Piece> createBeforePawn(ColorType color, Universe* universe, Vector xyzw) {
    return std::make_shared<BeforePawn>(color, universe, xyzw);
}

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

    Vector entry21 = pos + entries[0];
    Vector entry22 = pos + entries[1];
    Vector entry51 = pos + entries[2];
    Vector entry52 = pos + entries[3];

    std::shared_ptr<Piece> target21 = universe_->getPiece(entry21);
    std::shared_ptr<Piece> target22 = universe_->getPiece(entry22);
    std::shared_ptr<Piece> target51 = universe_->getPiece(entry51);
    std::shared_ptr<Piece> target52 = universe_->getPiece(entry52);

    std::vector<Vector> validMoves;

    if (target21 == nullptr) {
        validMoves.push_back(entries[0]);
        if (target22 == nullptr) {
            validMoves.push_back(entries[1]);
        }
    }
    if (target51 == nullptr) {
        validMoves.push_back(entries[2]);
        if (target22 == nullptr) {
            validMoves.push_back(entries[3]);
        }
    }

    if (target51->getType() == PieceType::NotFound && target52 == nullptr) {
        validMoves.push_back(entries[3]);
        universe_->addCrossBlankPiece(pos, Vector{entry51[2], entry51[3]});
    }

    return validMoves;
}

std::shared_ptr<Piece> BeforePawn::clone() const {
    return std::make_shared<BeforePawn>(*this);
}

