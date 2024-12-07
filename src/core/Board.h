#pragma once

#include <BeforePawn.h>
#include <Bishop.h>
#include <King.h>
#include <Knight.h>
#include <vector>
#include <memory>
#include <Piece.h>
#include <Queen.h>
#include <Rook.h>

class Universe;
const int BOARD_SIZE = 8;



const std::vector<std::tuple<int, int, PieceType, ColorType, std::shared_ptr<Piece>(*)(ColorType, Universe*, Vector)>> initialBoardData = {
    {0, 0, PieceType::Rook, ColorType::Black, &createRook},
    {1, 0, PieceType::Knight, ColorType::Black, &createKnight},
    {2, 0, PieceType::Bishop, ColorType::Black, &createBishop},
    {3, 0, PieceType::Queen, ColorType::Black, &createQueen},
    {4, 0, PieceType::King, ColorType::Black, &createKing},
    {5, 0, PieceType::Bishop, ColorType::Black, &createBishop},
    {6, 0, PieceType::Knight, ColorType::Black, &createKnight},
    {7, 0, PieceType::Rook, ColorType::Black, &createRook},

    {0, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},
    {1, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},
    {2, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},
    {3, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},
    {4, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},
    {5, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},
    {6, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},
    {7, 1, PieceType::BeforePawn, ColorType::Black, &createBeforePawn},

    {0, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},
    {1, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},
    {2, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},
    {3, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},
    {4, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},
    {5, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},
    {6, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},
    {7, 6, PieceType::BeforePawn, ColorType::White, &createBeforePawn},

    {0, 7, PieceType::Rook, ColorType::White, &createRook},
    {1, 7, PieceType::Knight, ColorType::White, &createKnight},
    {2, 7, PieceType::Bishop, ColorType::White, &createBishop},
    {3, 7, PieceType::Queen, ColorType::White, &createQueen},
    {4, 7, PieceType::King, ColorType::White, &createKing},
    {5, 7, PieceType::Bishop, ColorType::White, &createBishop},
    {6, 7, PieceType::Knight, ColorType::White, &createKnight},
    {7, 7, PieceType::Rook, ColorType::White, &createRook}
};


class Board {
public:
    Board(Universe* universe, Vector zw);
    ~Board();

    void initialize();

    std::shared_ptr<Piece> getPiece(int x, int y) const;
    void setPiece(int x, int y, std::shared_ptr<Piece> piece);
    void deletePiece(int x, int y);
    void updatePiecesXYZW();

    Vector getZW();
    void setZW(Vector zw);

    void printBoard() const;

    std::shared_ptr<Board> clone() const;

    std::vector<std::shared_ptr<Piece>> getColorPieces(ColorType color) const;

private:
    Universe* universe_;
    std::vector<std::vector<std::shared_ptr<Piece>>> grid_;
    Vector zw_;
};
