#pragma once

#include <vector>
#include <memory>
#include "Board.h"

class Timeline {
public:
    Timeline();
    ~Timeline();

    void initialize();

    void addBoardState(const Board& board);

    Board getBoardState(int index) const;

    int getLength() const;

private:
    std::vector<Board> boards_;
    Board parent_;
    int height_;
};
