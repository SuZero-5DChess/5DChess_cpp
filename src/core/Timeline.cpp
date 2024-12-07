#include "Timeline.h"

Timeline::Timeline(Universe* universe, Board* parent, int zOffset)
    : universe_(universe), parent_(parent), zOffset_(zOffset) {
}

Timeline::~Timeline() {}

void Timeline::initialize() {}

void Timeline::addBoardState(const std::shared_ptr<Board> board) {
    boards_.push_back(board);
}

std::shared_ptr<Board> Timeline::getBoardState(int index) const {
    int relativeIndex = index - zOffset_;
    if (relativeIndex >= 0 && relativeIndex < boards_.size()) {
        return boards_[relativeIndex];
    }
    return nullptr;
}

int Timeline::getLength() const {
    return boards_.size();
}

int Timeline::getOffset() const {
    return zOffset_;
}
