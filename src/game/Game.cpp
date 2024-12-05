#include "Game.h"

Game::Game()
    : currentPlayer_(ColorType::White) {
    Timeline initialTimeline;
    Board initialBoard;
    initialBoard.initialize();
    initialTimeline.initialize();
    initialTimeline.addBoardState(initialBoard);
    universe_.addTimeline(initialTimeline);
}

Game::~Game() {}

void Game::start() {
    while (true) {
    }
}

void Game::handleMove() {
}

void Game::checkGameState() {
}

void Game::switchPlayer() {
    currentPlayer_ = (currentPlayer_ == ColorType::White) ? ColorType::Black : ColorType::White;
}
