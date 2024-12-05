#include "Timeline.h"

Timeline::Timeline() {
}

Timeline::~Timeline() {}

void Timeline::initialize() {
    // TODO: Initialize

//      addBoardState(first);
//      parent_ = parent;
//      height_ = height;
}

void Timeline::addBoardState(const Board& board) {
    boards_.push_back(board);
}

Board Timeline::getBoardState(int index) const {
    if (index >= 0 && index < boards_.size()) {
        return boards_[index];
    }
    return Board();
}

int Timeline::getLength() const {
    return boards_.size();
}
