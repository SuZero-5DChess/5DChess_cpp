#include <Universe.h>

#include <utility>

Board::Board(Universe* universe, Vector zw): universe_(universe) {
    zw_ = std::move(zw);
    grid_.resize(BOARD_SIZE, std::vector<std::shared_ptr<Piece>>(BOARD_SIZE, nullptr));
}

Board::~Board() {}

void Board::initialize() {
    for (const auto& [x, y, type, color, creator] : initialBoardData) {
        setPiece(x, y, creator(color, universe_, Vector{x, y, zw_[0], zw_[1]}));
    }
}

std::shared_ptr<Piece> Board::getPiece(int x, int y) const {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        return grid_[x][y];
    }
    return universe_->returnNotFound();
}

void Board::setPiece(int x, int y, std::shared_ptr<Piece> piece) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        grid_[x][y] = piece;
    }
}

void Board::deletePiece(int x, int y) {
    grid_[x][y] = nullptr;
}

void Board::updatePiecesMoves() {
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            std::shared_ptr<Piece> piece = getPiece(x, y);
            if (piece) {
                piece->setXYZW(Vector{x, y, zw_[0], zw_[1]});
                piece->setValidMoves(piece->getValidMoves());
            }
        }
    }
}


Vector Board::getZW() {
    return zw_;
}

void Board::setZW(Vector zw) {
    zw_ = zw;
}



void Board::printBoard() const {
    for (int y = BOARD_SIZE - 1; y >= 0; --y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            auto piece = getPiece(x, y);
            if (piece) {
                std::cout << piece->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

std::shared_ptr<Board> Board::clone() const {
    auto newBoard = std::make_shared<Board>(universe_, zw_);

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            std::shared_ptr<Piece> piece = getPiece(x, y);
            if (piece) {
                auto newPiece = piece->clone();
                newBoard->grid_[x][y] = newPiece;
            }
        }
    }

    return newBoard;
}

std::vector<std::shared_ptr<Piece>> Board::getColorPieces(ColorType color) const {
    std::vector<std::shared_ptr<Piece>> pieces;

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            std::shared_ptr<Piece> piece = getPiece(x, y);
            if (piece && piece->getColor() == color) {
                pieces.push_back(piece);
            }
        }
    }

    return pieces;
}

