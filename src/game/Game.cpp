#include "Game.h"

#include <algorithm>
#include <regex>

#include <AfterPawn.h>
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
    Board board0 = Board(&universe_, Vector{0, 0});
    board0.initialize();
    Board board1 = Board(&universe_, Vector{1, 0});
    board1.initialize();
    timeline.addBoardState(std::make_shared<Board>(board0));
    timeline.addBoardState(std::make_shared<Board>(board1));
    universe_.addTimeline(std::make_shared<Timeline>(timeline), false);

    for (int x = 0; x <= 7 ; ++x) {
        for (int y : {0, 1, 6, 7}) {
            std::shared_ptr<Piece> b1Piece = board1.getPiece(x, y);
            b1Piece->setValidMoves(b1Piece->getValidMoves());
        }
    }
}

void Game::start() {
    while (true) {
        std::vector<Vector> move = readMove();
        std::shared_ptr<Piece> piece = universe_.getPiece(move[0]);
        handleMove(piece, move[1]);

        if (!canNextTurn()) { continue; }

        std::vector<Vector> remainMoves = getMovablePieces();
        if (remainMoves.empty()) {
            universe_.setPresent(universe_.getPresent() + 1);
            switchPlayer();
            std::cout << "Changed to Player" << currentPlayer_;
        } else {
            if (getYesNo()) {
                continue;
            } else {
                universe_.setPresent(universe_.getPresent() + 1);
                switchPlayer();
            }
        }
    }
}

void Game::handleMove(std::shared_ptr<Piece> piece, Vector dest) {
    Vector pos = piece->getXYZW();
    ColorType color = piece->getColor();
    int forward_up = color == ColorType::White ? 1 : -1;

    // move
    piece->setXYZW(dest);

    universe_.setPiece(pos, nullptr);


    // take
    std::shared_ptr<Piece> destPiece = universe_.getPiece(dest);

    if (destPiece != nullptr) {
        // TODO some operation?
        if (destPiece->getType() == PieceType::King) {
            // TODO game over

            std::cout << "Player" << currentPlayer_ << "win!";
            exit(0);
        }
    }

    Vector enRight = {1, -1 * forward_up, 0, 0};
    Vector enLeft = {-1, -1 * forward_up, 0, 0};

    if (piece->getType() == PieceType::AfterPawn
        && dest - pos == enRight
        && destPiece == nullptr) {
        universe_.setPiece(pos + Vector{1, 0, 0, 0}, nullptr);
    }

    if (piece->getType() == PieceType::AfterPawn
        && dest - pos == enLeft
        && destPiece == nullptr) {
        universe_.setPiece(pos + Vector{-1, 0, 0, 0}, nullptr);
    }

    if (piece->getType() == PieceType::AfterPawn
        && (forward_up == 1 ? dest[1] == 0 : dest[1] == 7)) {
        piece = createQueen(color, &universe_, piece->getXYZW());
    }

    if (piece->getType() == PieceType::BeforePawn) {
        piece = createAfterPawn(color, &universe_, piece->getXYZW());
    }

    universe_.setPiece(dest, piece);

    // create new board

    std::shared_ptr<Board> newDestBoard = universe_.getTimeline(dest[3])->getBoardState(dest[2])->clone();

    // time travel

    std::shared_ptr<Timeline> destTimeline = universe_.getTimeline(dest[3]);

    if (pos[2] == dest[2] && pos[3] == dest[3]) {
        // in-board move
        destTimeline->addBoardState(newDestBoard);
        newDestBoard->setZW(Vector{dest[2] + 1, dest[3]});
        newDestBoard->updatePiecesMoves();

    }
    else if (destTimeline->getLength() + destTimeline->getOffset() - 1 == dest[2]) {
        // to active board, no timeline created
        destTimeline->addBoardState(newDestBoard);
        newDestBoard->setZW(Vector{dest[2] + 1, dest[3]});

        std::shared_ptr<Board> newOriginBoard = universe_.getTimeline(pos[3])->getBoardState(pos[2])->clone();
        universe_.getTimeline(pos[3])->addBoardState(newOriginBoard);
        newOriginBoard->setZW(Vector{pos[2] + 1, pos[3]});

        newDestBoard->updatePiecesMoves();
        newOriginBoard->updatePiecesMoves();


    }
    else {
        // to inactive board, create timeline
        Timeline createTimeline = Timeline(
            &universe_,
            destTimeline->getBoardState(dest[2]).get(),
            dest[2] + 1
        );
        createTimeline.addBoardState(newDestBoard);

        int timelineCount = universe_.getTimelineCount();
        int currentTimeline0 = universe_.getCurrentTimeline0();
        bool isPositive = forward_up == 1;

        int timelineIndex = isPositive ? timelineCount - currentTimeline0 : - currentTimeline0 - 1;
        universe_.addTimeline(std::make_shared<Timeline>(createTimeline), isPositive);
        newDestBoard->setZW(Vector{createTimeline.getOffset(), timelineIndex});

        std::shared_ptr<Board> newOriginBoard = universe_.getTimeline(pos[3])->getBoardState(pos[2])->clone();
        universe_.getTimeline(pos[3])->addBoardState(newOriginBoard);
        newOriginBoard->setZW(Vector{pos[2] + 1, pos[3]});

        newDestBoard->updatePiecesMoves();
        newOriginBoard->updatePiecesMoves();

        universe_.setPresent(dest[2] < universe_.getPresent() ? dest[2] : universe_.getPresent());
    }
}

bool Game::canNextTurn() {
    Vector timelinesIndex = universe_.getActiveTimelines();
    int present = universe_.getPresent();
    for (int i = timelinesIndex[0]; i <= timelinesIndex[1]; i++) {
        std::shared_ptr<Timeline> iterTimeline = universe_.getTimeline(i);
        if (iterTimeline->getLength() + iterTimeline->getOffset() - 1 == present) {
            return false;
        }
    }
    return true;
}

std::vector<Vector> Game::getMovablePieces() {
    std::vector<Vector> movablePieces;

    Vector timelinesIndex = universe_.getActiveTimelines();
    for (int i = timelinesIndex[0]; i <= timelinesIndex[1]; i++) {
        std::shared_ptr<Timeline> iterTimeline = universe_.getTimeline(i);
        int turn = currentPlayer_ == ColorType::White ? 1 : 0;
        if ((iterTimeline->getLength() + iterTimeline->getOffset() - 1) % 2 != turn) { continue; }

        std::vector<std::shared_ptr<Piece>> pieces = iterTimeline->getBoardState(
            iterTimeline->getLength() - 1 + iterTimeline->getOffset()
        )->getColorPieces(currentPlayer_);
        for (const auto &piece : pieces) {
            if (piece->readValidMoves().empty()) { continue; }

            movablePieces.push_back(piece->getXYZW());
        }
    }

    return movablePieces;
}


void Game::switchPlayer() {
    currentPlayer_ = (currentPlayer_ == ColorType::White) ? ColorType::Black : ColorType::White;
}

std::vector<Vector> Game::readMove() {
    // (a, b, c, d)->(e, f, g, h)
    std::regex pattern(R"(\(\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*\)\s*->\s*\(\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*\))");
    std::string input;
    std::smatch match;

    std::vector<Vector> movablePieces = getMovablePieces();

    for (const auto& element: movablePieces) {
        std::cout << element << std::endl;
    }

    while (true) {
        std::cout << "Enter input in the format (a,b,c,d)->(e,f,g,h): ";
        std::getline(std::cin, input);

        if (std::regex_match(input, match, pattern)) {
            int a = std::stoi(match[1].str());
            int b = std::stoi(match[2].str());
            int c = std::stoi(match[3].str());
            int d = std::stoi(match[4].str());

            Vector startPosition = Vector{a, b, c, d};

            if (std::find(
                movablePieces.begin(),
                movablePieces.end(),
                startPosition
            ) == movablePieces.end()) {
                std::cout << "Invalid start position";
                continue;
            }

            std::shared_ptr<Piece> piece = universe_.getPiece(startPosition);

            int e = std::stoi(match[5].str());
            int f = std::stoi(match[6].str());
            int g = std::stoi(match[7].str());
            int h = std::stoi(match[8].str());

            Vector endDirection = Vector{e, f, g, h} - startPosition;

            std::vector<Vector> dests = piece->readValidMoves();

            if (std::find(
                dests.begin(),
                dests.end(),
                endDirection
                ) == dests.end()) {
                std::cout << "Invalid end position";
                continue;
            }

            return {Vector{a, b, c, d}, Vector{e, f, g, h}};
        } else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
}

bool Game::getYesNo() {
    std::string input;
    while (true) {
        std::cout << "you can continue, Y/N? ";
        std::getline(std::cin, input);

        if (!input.empty()) {
            char firstChar = std::tolower(input[0]);

            if (firstChar == 'y') {
                return true;
            } else if (firstChar == 'n') {
                return false;
            }
        }

        std::cout << "Invalid input. Please enter Y or N." << std::endl;
    }
}
