#pragma once

#include <vector>
#include "Board.h"

class Universe;

class Timeline {
public:
    Timeline(Universe* universe, Board* parent, int w);
    ~Timeline();

    void initialize();

    void addBoardState(const std::shared_ptr<Board> board);

    std::shared_ptr<Board> getBoardState(int index) const;

    int getLength() const;

private:
    Universe* universe_;
    std::vector<std::shared_ptr<Board>> boards_;
    Board* parent_;
    int w_;
};
