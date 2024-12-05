#include "Timeline.h"

Timeline::Timeline(Universe* universe, Board* parent)
    : universe_(universe), parent_(parent), w_(0) { // TODO: change w
}

Timeline::~Timeline() {}

void Timeline::initialize() {
    // TODO: Initialize

//      addBoardState(first);
//      parent_ = parent;
//      height_ = height;
}

void Timeline::addBoardState(const std::shared_ptr<Board> board) {
    boards_.push_back(board);
}

std::shared_ptr<Board> Timeline::getBoardState(int index) const {
    if (index >= 0 && index < boards_.size()) {
        return boards_[index];
    }
    return nullptr;
}

int Timeline::getLength() const {
    return boards_.size();
}
