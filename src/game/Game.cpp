#include "Game.h"

#include <regex>
#include <AfterPawn.h>
#include <parser.h>
#include <Queen.h>

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

    initializeGame();
}

void Game::initializeGame() {
    std::string notation =
        R"(
1.(0T1)Ng1f3/(0T1)Ng8f6

2.(0T2)d2d4/(0T2)d7d5
3.(0T3)c2c3/(0T3)c7c6
4.(0T4)Bc1f4/(0T4)Bc8f5
5.(0T5)e2e3/(0T5)e7e6
6.(0T6)Bf1d3/(0T6)Bf5g6
7.(0T7)Bd3g6/(0T7)h7g6
8.(0T8)Nb1d2/(0T8)Bf8d6
9.(0T9)Bf4d6/(0T9)Qd8d6
10.(0T10)Nf3e5/(0T10)Nb8d7
11.(0T11)Nd2f3/(0T11)Rh8h5
12.(0T12)Ne5d7/(0T12)Qd6d7
13.(0T13)Qd1e2/(0T13)Qd7d6
14.(0T14)Nf3e5/(0T14)Rh5e5
15.(0T15)d4e5/(0T15)Qd6e5
16.(0T16)Qe2f3/(0T16)d5d4
17.(0T17)Qf3g3/(0T17)Qe5b5
18.(0T18)Qg3h4/(0T18)Qb5>>(0T15)e2
19.(-1T16)Ke1e2/(-1T16)Nf6e4
20.(0T19)Qh4>>(0T1)h4/(1T1)Ng8f6
21.(1T2)e2e3/(1T2)d7d5
22.(1T3)Qh4f6/(1T3)g7f6
23.(1T4)Qd1h5/(1T4)Bc8e6
24.(1T5)Bf1b5/(1T5)c7c6
25.(1T6)Qh5>>(1T4)f7/(2T4)Ke8f7
26.(2T5)Qd1h5/(2T5)Kf7g8
27.(2T6)Bf1b5/(1T6)Qd8>>(1T4)d6
28.(-2T5)Qh5f7/(-2T5)Ke8f7
29.(-2T6)Bf1b5/(-2T6)Kf7>>(-2T5)f7
30.(-3T6)Bf1b5

        )";

    notationStream_ = std::istringstream(notation);
    round_ = 1;

    currentPlayer_ = ColorType::White;
}

void Game::readAndExecuteMove() {
    std::string line;

    while (std::getline(notationStream_, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) continue;

        size_t dotPos = line.find('.');
        if (dotPos != std::string::npos) {
            line = line.substr(dotPos + 1);
        }

        size_t slashPos = line.find('/');
        std::string moveWhite = line;
        std::string moveBlack = "";

        if (slashPos != std::string::npos) {
            moveWhite = line.substr(0, slashPos);
            moveBlack = line.substr(slashPos + 1);
        }

        moveWhite.erase(0, moveWhite.find_first_not_of(" \t\r\n"));
        moveWhite.erase(moveWhite.find_last_not_of(" \t\r\n") + 1);
        moveBlack.erase(0, moveBlack.find_first_not_of(" \t\r\n"));
        moveBlack.erase(moveBlack.find_last_not_of(" \t\r\n") + 1);

        if (!moveWhite.empty()) {
            currentPlayer_ = ColorType::White;
            std::cout << "Player White's move:" <<  moveWhite << std::endl;

            std::vector<std::string> moveList = splitMoves(moveWhite);
            for (const std::string& moveStr : moveList) {
                processAndExecuteMove(moveStr);
            }

            universe_.setPresent(universe_.getPresent() + 1);
        }

        if (!moveBlack.empty()) {
            currentPlayer_ = ColorType::Black;
            std::cout << "Player Black's move:" <<  moveBlack <<  std::endl;

            std::vector<std::string> moveList = splitMoves(moveBlack);
            for (const std::string& moveStr : moveList) {
                processAndExecuteMove(moveStr);
            }

            universe_.setPresent(universe_.getPresent() + 1);
        }
        return;
    }
}

void Game::processAndExecuteMove(const std::string& moveStr) {
    try {
        std::vector<Vector> moveVectors = processMove(moveStr, round_, currentPlayer_, std::make_shared<Universe>(universe_));

        if (moveVectors.size() != 2) {
            std::cout << "Invalid move format in: " << moveStr << std::endl;
            return;
        }

        Vector startPos = moveVectors[0];
        Vector endPos = moveVectors[1];

        std::shared_ptr<Piece> piece = universe_.getPiece(startPos);

        if (!piece) {
            std::cout << "Invalid move: No piece at the start position (" << startPos << ")." << std::endl;
            return;
        }

        if (piece->getColor() != currentPlayer_) {
            std::cout << "Invalid move: Attempting to move opponent's piece." << std::endl;
            return;
        }

        handleMove(piece, endPos);
    } catch (const std::exception& e) {
        std::cout << "Skipping annotation or invalid move: " << moveStr << " (" << e.what() << ")" << std::endl;
        return;
    }
}


void Game::start() {
    while (notationStream_) {
        readAndExecuteMove();
        round_++;
    }

    std::cout << "Game over." << std::endl;
}

void Game::handleMove(std::shared_ptr<Piece> piece, Vector dest) {
    Vector pos = piece->getXYZW();
    ColorType color = piece->getColor();
    int forward_up = (color == ColorType::White) ? 1 : -1;

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

    // create new board

    std::shared_ptr<Board> newDestBoard = universe_.getTimeline(dest[3])->getBoardState(dest[2])->clone();

    // time travel

    std::shared_ptr<Timeline> destTimeline = universe_.getTimeline(dest[3]);

    if (pos[2] == dest[2] && pos[3] == dest[3]) {
        // in-board move
        destTimeline->addBoardState(newDestBoard);
        newDestBoard->setZW(Vector{dest[2] + 1, dest[3]});

        // move
        piece->setXYZW(dest + Vector{0, 0, 1, 0});
        universe_.setPiece(pos + Vector{0, 0, 1, 0}, nullptr);

        // en pass
        Vector enRight = {1, -1 * forward_up, 0, 0};
        Vector enLeft = {-1, -1 * forward_up, 0, 0};

        if (piece->getType() == PieceType::AfterPawn
            && dest - pos == enRight
            && destPiece == nullptr) {
            universe_.setPiece(pos + Vector{1, 0, 1, 0}, nullptr);
        }

        if (piece->getType() == PieceType::AfterPawn
            && dest - pos == enLeft
            && destPiece == nullptr) {
            universe_.setPiece(pos + Vector{-1, 0, 1, 0}, nullptr);
        }

        if (piece->getType() == PieceType::AfterPawn
            && (forward_up == 1 ? dest[1] == 0 : dest[1] == 7)) {
            piece = createQueen(color, &universe_, piece->getXYZW());
        }

        if (piece->getType() == PieceType::BeforePawn) {
            piece = createAfterPawn(color, &universe_, piece->getXYZW());
        }

        // castle
        if (piece->getType() == PieceType::King) {
            Vector direction = dest - pos;
            if (direction[0] == 2) {
                Vector rookPos = Vector{7, forward_up == 1 ? 7 : 0, pos[2] + 1, pos[3]};
                Vector rookDest = Vector{5, forward_up == 1 ? 7 : 0, pos[2] + 1, pos[3]};
                std::shared_ptr<Piece> rook = universe_.getPiece(rookPos);
                rook->setXYZW(rookDest);
                universe_.setPiece(rookPos, nullptr);
                universe_.setPiece(rookDest, rook);
            }
            if (direction[0] == -2) {
                Vector rookPos = Vector{0, forward_up == 1 ? 7 : 0, pos[2] + 1, pos[3]};
                Vector rookDest = Vector{3, forward_up == 1 ? 7 : 0, pos[2] + 1, pos[3]};
                std::shared_ptr<Piece> rook = universe_.getPiece(rookPos);
                rook->setXYZW(rookDest);
                universe_.setPiece(rookPos, nullptr);
                universe_.setPiece(rookDest, rook);
            }
        }

        universe_.setPiece(dest + Vector{0, 0, 1, 0}, piece);
        newDestBoard->updatePiecesXYZW();

    }
    else if (destTimeline->getLength() + destTimeline->getOffset() - 1 == dest[2]) {
        // to active board, no timeline created
        destTimeline->addBoardState(newDestBoard);
        newDestBoard->setZW(Vector{dest[2] + 1, dest[3]});
        piece->setXYZW(dest + Vector{0, 0, 1, 0});
        universe_.setPiece(dest + Vector{0, 0, 1, 0}, piece);

        std::shared_ptr<Board> newOriginBoard = universe_.getTimeline(pos[3])->getBoardState(pos[2])->clone();
        universe_.getTimeline(pos[3])->addBoardState(newOriginBoard);
        universe_.setPiece(pos + Vector{0, 0, 1, 0}, nullptr);
        newOriginBoard->setZW(Vector{pos[2] + 1, pos[3]});

        newDestBoard->updatePiecesXYZW();
        newOriginBoard->updatePiecesXYZW();


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
        universe_.setPiece(Vector{dest[0], dest[1], createTimeline.getOffset(), timelineIndex}, piece);
        piece->setXYZW(Vector{dest[0], dest[1], createTimeline.getOffset(), timelineIndex});

        std::shared_ptr<Board> newOriginBoard = universe_.getTimeline(pos[3])->getBoardState(pos[2])->clone();
        universe_.getTimeline(pos[3])->addBoardState(newOriginBoard);
        newOriginBoard->setZW(Vector{pos[2] + 1, pos[3]});
        universe_.setPiece(pos + Vector{0, 0, 1, 0}, nullptr);

        newDestBoard->updatePiecesXYZW();
        newOriginBoard->updatePiecesXYZW();

        Vector activeTimeline = universe_.getActiveTimelines();

        if (activeTimeline[0] <= timelineIndex && timelineIndex <= activeTimeline[1]) {
            universe_.setPresent(dest[2] < universe_.getPresent() ? dest[2] : universe_.getPresent());
        }
        else {
            universe_.setPresent(universe_.getPresent());
        }
    }
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
            piece->setValidMoves(piece->getValidMoves());
            if (piece->readValidMoves().empty()) { continue; }

            movablePieces.push_back(piece->getXYZW());
        }
    }

    return movablePieces;
}

void Game::switchPlayer() {
    currentPlayer_ = (currentPlayer_ == ColorType::White) ? ColorType::Black : ColorType::White;
}
