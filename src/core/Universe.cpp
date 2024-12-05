#include "Universe.h"

#include <Notfound.h>

Universe::Universe() {
    auto notfound = std::make_shared<Piece>(PieceType::NotFound, ColorType::White, nullptr);
    notfound_ = notfound;
}

Universe::~Universe() {}

std::shared_ptr<Piece> Universe::returnNotFound() const {
    return notfound_;
}


void Universe::addTimeline(const std::shared_ptr<Timeline> timeline) {
    timelines_.push_back(timeline);
}

std::shared_ptr<Timeline> Universe::getTimeline(int index) const {
    if (index >= 0 && index < timelines_.size()) {
        return timelines_[index];
    }
    return nullptr;
}

int Universe::getTimelineCount() const {
    return timelines_.size();
}

std::shared_ptr<Piece> Universe::getPiece(Vector xyzw) const {
    int x = xyzw[0];
    int y = xyzw[1];
    int z = xyzw[2];
    int w = xyzw[3];

    std::shared_ptr<Timeline> timeline = getTimeline(w);
    if (timeline == nullptr) return notfound_;

    std::shared_ptr<Board> board = timeline->getBoardState(z);
    if (board == nullptr) return notfound_;

    std::shared_ptr<Piece> piece = board->getPiece(x, y);
    return piece;
}

