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
1. Nf3 / Nf6
2. d4 / d5
3. c3 / c6
4. Bf4 / Bf5
5. e3 / e6
6. Bd3 / Bxd3
7. Qxd3 / Bd6
8. Bxd6 / Qxd6
9. Nbd2 / Nbd7
10. Qc2 / Qc7
11. Qb3 / Qb6
12. a4 / Qxb3
13. Nxb3 / Ne4
14. Nbd2 / Ndf6
15. Nxe4 / Nxe4
16. Nd2 / Nd6
17. Kg1 / Kg8
18. f4 / f5
19. a5 / b5
20. b4 / Kh8
21. Kh1 / Rg8
22. h4 / Raf8
23. Rf3 / Rf6
24. Rg1 / Rh6
25. Rh3 / Rg6
26. Kh2 / Rg4
27. Rf1 / Rf8
28. Rff3 / Ne8
29. Kh1 / Nf6
30. Rh2 / Nh5
31. Kg1 / Rf6
32. Rfh3 / e5
33. dxe5 / Rfg6
34. Nf3 / h6
35. Ng5 / Kg8
36. Kf1 / hxg5
37. hxg5 / Ng3
38. Rxg3 / Rxg3
39. Kf2 / Rg4
40. g3 / c5
41. Kf3 / cxb4
42. Rd2 / Re6
43. Rxd5 / Re8
44. cxb4 / Rc8
45. e6 / Kh7
46. Rc5 / Rd8
47. Rc1 / Rh4
48. gxh4 / Rd2
49. g6 / Kh6
50. Rh1 / Rc2
51. (0T51)Rh1>>(0T39)h1~ (>L1) / (1T39)Rh6
52. (1T40)Rxh6 / (1T40)gxh6
53. (1T41)Rxh6 / (1T41)Rxe3
54. (1T42)Rg6 / (1T42)Kf8
55. (1T43)Rf6 / (1T43)Kg8
56. (1T44)Rg6 / (1T44)Kf8
57. (1T45)Rf6 / (1T45)Kg8
58. (1T46)Rg6 / (1T46)Kf8
59. (1T47)Rf6 / (1T47)Kg8
60. (1T48)Rg6 / (1T48)Kf8
61. (1T49)Rh6 / (0T51)Rc2>>x(0T10)c2~ (>L-1)
62. (-1T11)Ke1>>(0T11)d1~ (>L2) / (-1T11)Rxd2 (2T11)Qb6
63. (-1T12)Nxd2 (2T12)Nb3 / (2T12)Qa6 (-1T12)Ng4
64. (-1T13)Rhf1 (2T13)Ng5 / (2T13)Ng4 (-1T13)Qxh2
65. (-1T14)Nf3 (2T14)Nxh7 / (-1T14)Qxg2 (2T14)Rxh7
66. (2T15)Qxh7 (-1T15)Rg1 / (2T15)Nxe3 (-1T15)Nxe3
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
                Rook* rookPtr = static_cast<Rook*>(rook.get());
                rookPtr->setIsMoved();
                King* kingPtr = static_cast<King*>(piece.get());
                kingPtr->setIsMoved();
                universe_.setPiece(rookPos, nullptr);
                universe_.setPiece(rookDest, rook);
            }
            if (direction[0] == -2) {
                Vector rookPos = Vector{0, forward_up == 1 ? 7 : 0, pos[2] + 1, pos[3]};
                Vector rookDest = Vector{3, forward_up == 1 ? 7 : 0, pos[2] + 1, pos[3]};
                std::shared_ptr<Piece> rook = universe_.getPiece(rookPos);
                rook->setXYZW(rookDest);
                Rook* rookPtr = static_cast<Rook*>(rook.get());
                rookPtr->setIsMoved();
                King* kingPtr = static_cast<King*>(piece.get());
                kingPtr->setIsMoved();
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
