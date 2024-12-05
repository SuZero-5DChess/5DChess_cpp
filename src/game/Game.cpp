#include "Game.h"

#include <AfterPawn.h>
#include <BeforePawn.h>
#include <Bishop.h>
#include <Knight.h>
#include <Queen.h>
#include <Rook.h>

Game::Game()
    : currentPlayer_(ColorType::White) {
    initialize();
}

Game::~Game() {}

void Game::initialize() {
    Timeline timeline = Timeline(&universe_, nullptr, 0);
    Board board0 = Board(&universe_);
    board0.initialize();
    Board board1 = Board(&universe_);
    board1.initialize();
    timeline.addBoardState(std::make_shared<Board>(board0));
    timeline.addBoardState(std::make_shared<Board>(board1));
    universe_.addTimeline(std::make_shared<Timeline>(timeline), false);

    for (int x = 0; x <= 7 ; ++x) {
        for (int y : {0, 1, 6, 7}) {
            std::shared_ptr<Piece> b0Piece = board0.getPiece(x, y);
            b0Piece->setValidMoves(b0Piece->getValidMoves());

            std::shared_ptr<Piece> b1Piece = board1.getPiece(x, y);
            b1Piece->setValidMoves(b1Piece->getValidMoves());
        }
    }
}


void Game::start() {
    while (true) {
    }
}

void Game::handleMove(std::shared_ptr<Piece> piece, Vector dest) {
    Vector pos = piece->getXYZW();
    ColorType color = piece->getColor();
    int forward_up = color == ColorType::White ? 1 : -1;



    // move
    piece->setValidMoves(piece->getValidMoves());
    piece->setXYZW(dest);

    universe_.setPiece(pos, nullptr);

    // take
    if (universe_.getPiece(dest) != nullptr) {
        // TODO some operation

    // TODO check game over
    }

    // TODO en pass

    universe_.setPiece(dest, piece);

    // check the start point and update

    for (const auto& direction: queenDirections) {
        Vector current_target = pos + direction;

        while (true) {
            std::shared_ptr<Piece> place = universe_.getPiece(current_target);
            if (place != nullptr) {
                PieceType type = place->getType();
                if (type != PieceType::NotFound) {
                    if (type == PieceType::Pawn) {
                        break;
                    }
                    int count = 0;
                    if (direction[0] == 0) count++;
                    if (direction[1] == 0) count++;
                    if (direction[2] == 0) count++;
                    if (direction[3] == 0) count++;
                    if (type == PieceType::Queen) {
                        Queen* queenPtr = static_cast<Queen*>(place.get());
                        queenPtr->updateDirection(pos, direction * -1);
                        break;
                    }
                    else if (type == PieceType::Rook
                        && count == 3) {
                        Rook* rookPtr = static_cast<Rook*>(place.get());
                        rookPtr->updateDirection(pos, direction * -1);
                        break;
                    }
                    else if (type == PieceType::Bishop
                        && count == 2) {
                        Bishop* bishopPtr = static_cast<Bishop*>(place.get());
                        bishopPtr->updateDirection(pos, direction * -1);
                    }
                    break;
                }
            }
        }
    }

    for (const auto& direction: knightDirections) {
        Vector current_target = pos + direction;
        std::shared_ptr<Piece> place = universe_.getPiece(current_target);
        if (place->getType() == PieceType::Knight) {
            Knight* knightPtr = static_cast<Knight*>(place.get());
            knightPtr->updateDirection(direction);
        }
    }

    std::vector<Vector> pawnEntries = {
        Vector{0, -1 * forward_up, 0, 0},
        Vector{1, -1 * forward_up, 0, 0},
        Vector{-1, -1 * forward_up, 0, 0},
        Vector{0, -2 * forward_up, 0, 0},
        Vector{0, 0, 0, -1 * forward_up},
        Vector{0, 0, 1, -1 * forward_up},
        Vector{0, 0, -1, -1 * forward_up},
        Vector{0, 0, 0, -2 * forward_up},
    };

    for (const auto& direction: pawnEntries) {
        Vector current_target = pos + direction;
        std::shared_ptr<Piece> place = universe_.getPiece(current_target);
        if (place->getType() == PieceType::Pawn) {
            place->setValidMoves(place->getValidMoves());
        }
    }


    // check the end point and update

    for (const auto& direction: queenDirections) {
        Vector current_target = pos + direction;

        while (true) {
            std::shared_ptr<Piece> place = universe_.getPiece(current_target);
            if (place != nullptr) {
                PieceType type = place->getType();
                if (type != PieceType::NotFound) {
                    if (type == PieceType::Pawn) {
                        break;
                    }
                    int count = 0;
                    if (direction[0] == 0) count++;
                    if (direction[1] == 0) count++;
                    if (direction[2] == 0) count++;
                    if (direction[3] == 0) count++;
                    if (type == PieceType::Queen) {
                        Queen* queenPtr = static_cast<Queen*>(place.get());
                        queenPtr->downdateDirection(pos, direction * -1);
                        break;
                    }
                    else if (type == PieceType::Rook
                        && count == 3) {
                        Rook* rookPtr = static_cast<Rook*>(place.get());
                        rookPtr->downdateDirection(pos, direction * -1);
                        break;
                    }
                    else if (type == PieceType::Bishop
                        && count == 2) {
                        Bishop* bishopPtr = static_cast<Bishop*>(place.get());
                        bishopPtr->downdateDirection(pos, direction * -1);
                    }
                    break;
                }
            }
        }
    }

    for (const auto& direction: knightDirections) {
        Vector current_target = pos + direction;
        std::shared_ptr<Piece> place = universe_.getPiece(current_target);
        if (place->getType() == PieceType::Knight) {
            Knight* knightPtr = static_cast<Knight*>(place.get());
            knightPtr->downdateDirection(direction);
        }
    }

    for (const auto& direction: pawnEntries) {
        Vector current_target = pos + direction;
        std::shared_ptr<Piece> place = universe_.getPiece(current_target);
        if (place->getType() == PieceType::Pawn) {
            place->setValidMoves(place->getValidMoves());
        }
    }

    // create new board

    std::shared_ptr<Board> newBoard = universe_.getTimeline(dest[3])->getBoardState(dest[2])->clone();

    // TODO: time travel


    // check crossing blank board update

    switchPlayer();
}

void Game::checkGameState() {
}

void Game::switchPlayer() {
    currentPlayer_ = (currentPlayer_ == ColorType::White) ? ColorType::Black : ColorType::White;
}
