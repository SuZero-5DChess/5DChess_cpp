#pragma once

#include <vector>
#include <memory>
#include <Piece.h>

class Universe;
const int BOARD_SIZE = 8;

const std::vector<std::tuple<int, int, PieceType, ColorType>> initialBoardData = {
    {0, 0, PieceType::Rook, ColorType::Black}, {1, 0, PieceType::Knight, ColorType::Black},
    {2, 0, PieceType::Bishop, ColorType::Black}, {3, 0, PieceType::Queen, ColorType::Black},
    {4, 0, PieceType::King, ColorType::Black}, {5, 0, PieceType::Bishop, ColorType::Black},
    {6, 0, PieceType::Knight, ColorType::Black}, {7, 0, PieceType::Rook, ColorType::Black},

    {0, 1, PieceType::Pawn, ColorType::Black}, {1, 1, PieceType::Pawn, ColorType::Black},
    {2, 1, PieceType::Pawn, ColorType::Black}, {3, 1, PieceType::Pawn, ColorType::Black},
    {4, 1, PieceType::Pawn, ColorType::Black}, {5, 1, PieceType::Pawn, ColorType::Black},
    {6, 1, PieceType::Pawn, ColorType::Black}, {7, 1, PieceType::Pawn, ColorType::Black},

    {0, 6, PieceType::Pawn, ColorType::White}, {1, 6, PieceType::Pawn, ColorType::White},
    {2, 6, PieceType::Pawn, ColorType::White}, {3, 6, PieceType::Pawn, ColorType::White},
    {4, 6, PieceType::Pawn, ColorType::White}, {5, 6, PieceType::Pawn, ColorType::White},
    {6, 6, PieceType::Pawn, ColorType::White}, {7, 6, PieceType::Pawn, ColorType::White},

    {0, 7, PieceType::Rook, ColorType::White}, {1, 7, PieceType::Knight, ColorType::White},
    {2, 7, PieceType::Bishop, ColorType::White}, {3, 7, PieceType::Queen, ColorType::White},
    {4, 7, PieceType::King, ColorType::White}, {5, 7, PieceType::Bishop, ColorType::White},
    {6, 7, PieceType::Knight, ColorType::White}, {7, 7, PieceType::Rook, ColorType::White}
};

class Board {
public:
    Board(Universe* universe);
    ~Board();

    void initialize();

    std::shared_ptr<Piece> getPiece(int x, int y) const;
    void setPiece(int x, int y, std::shared_ptr<Piece> piece);
    void deletePiece(int x, int y);

    void printBoard() const;

    std::shared_ptr<Board> clone() const;

    std::vector<std::shared_ptr<Piece>> getColorPieces(ColorType color) const;

private:
    Universe* universe_;
    std::vector<std::vector<std::shared_ptr<Piece>>> grid_;
};
