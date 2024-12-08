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
        1.(0T1)e2e3/(0T1)Ng8f6
        2.(0T2)b2b4/(0T2)e7e6
        3.(0T3)Qd1f3/(0T3)Nb8c6
        4.(0T4)Qf3g3/(0T4)Bf8b4
        5.(0T5)Ng1f3/(0T5)Rh8g8
        6.(0T6)Bf1d3/(0T6)Bb4d6
        7.(0T7)Qg3h4/(0T7)Nc6b4
        8.(0T8)Nb1a3/(0T8)Nb4d3
        9.(0T9)c2d3/(0T9)Qd8e7
        10.(0T10)Na3c4/(0T10)Bd6c5
        11.(0T11)a2a4/(0T11)b7b6
        12.(0T12)a4a5/(0T12)Bc8b7
        13.(0T13)a5b6/(0T13)a7b6
        14.(0T14)Ra1a8/(0T14)Bb7a8
        15.(0T15)Nc4e5/(0T15)b6b5
        16.(0T16)Ne5g4/(0T16)Nf6g4
        17.(0T17)Qh4g4/(0T17)Qe7f6
        18.(0T18)Qg4g3/(0T18)Bc5d6
        19.(0T19)Qg3g4/(0T19)Qf6g6
        20.(0T20)Qg4g6/(0T20)h7g6
        21.(0T21)e3e4/(0T21)f7f5
        22.(0T22)Nf3g5/(0T22)Bd6e7
        23.(0T23)Ng5h3/(0T23)f5e4
        24.(0T24)Nh3f4/(0T24)e4d3
        25.(0T25)f2f3/(0T25)Ba8d5
        26.(0T26)Nf4g6/(0T26)Ke8d8
        27.(0T27)Ng6e7/(0T27)Kd8e7
        28.(0T28)Bc1a3/(0T28)d7d6
        29.(0T29)Ke1g1/(0T29)g7g5
        30.(0T30)g2g4/(0T30)Rg8f8
        31.(0T31)Ba3b2/(0T31)e6e5
        32.(0T32)Rf1e1/(0T32)Ke7e6
        33.(0T33)Bb2d4/(0T33)Bd5f3
        34.(0T34)h2h3/(0T34)Rf8f4
        35.(0T35)Kg1h2/(0T35)Rf4d4
        36.(0T36)Re1f1/(0T36)Bf3e2
        37.(0T37)Rf1f2/(0T37)Rd4f4
        38.(0T38)Rf2>>(0T26)f2/(1T26)Be7f6
        39.(1T27)Ke1g1/(1T27)Rg8h8
        40.(1T28)Rf1e1/(1T28)Bf6>>(1T26)f4
        41.(-1T27)Ke1g1/(-1T27)Be7h4
        42.(1T29)Nf4>(-1T28)f4/(-1T28)Ke8f7
        43.(-1T29)Bc1a3/(-1T29)Bh4>(1T29)h2
        44.(1T30)Kg1f1 (-1T30)Ba3e7/(-1T30)Kf7e7 (1T30)Bh2g1
        45.(1T31)Kf1g1 (-1T31)Nf4g6/(1T31)Bd5c4 (-1T31)Ke7d8
        46.(1T32)Re1e6 (-1T32)Rf1e1
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
