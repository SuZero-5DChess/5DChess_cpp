#include <Universe.h>

Universe::Universe(): currentTimeline0_(-1), present_(1) {
    auto notfound = std::make_shared<Piece>(PieceType::NotFound, ColorType::White, nullptr, Vector{-1, -1, -1, -1});
    notfound_ = notfound;
}

Universe::~Universe() {}

std::shared_ptr<Piece> Universe::returnNotFound() const {
    return notfound_;
}


void Universe::addTimeline(const std::shared_ptr<Timeline>& timeline, bool isPositive) {
    if (isPositive) {
        timelines_.push_back(timeline);
    }
    else {
        timelines_.insert(timelines_.begin(), timeline);
        currentTimeline0_++;
    }
}

std::shared_ptr<Timeline> Universe::getTimeline(int index) const {
    int vectorIndex = currentTimeline0_ + index;
    if (vectorIndex >= 0 && vectorIndex < timelines_.size()) {
        return timelines_[vectorIndex];
    }
    return nullptr;
}

int Universe::getTimelineCount() const {
    return timelines_.size();
}

int Universe::getCurrentTimeline0() const {
    return currentTimeline0_;
}


void Universe::setPiece(const Vector& xyzw, const std::shared_ptr<Piece>& piece) const {
    int x = xyzw[0];
    int y = xyzw[1];
    int z = xyzw[2];
    int w = xyzw[3];
    getTimeline(w)->getBoardState(z)->setPiece(x, y, piece);
}


std::shared_ptr<Piece> Universe::getPiece(const Vector& xyzw) const {
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

Vector Universe::getActiveTimelines() {
    int length = getTimelineCount() - 1;
    int mid = 2 * currentTimeline0_;
    if (length > mid) return Vector{- currentTimeline0_, currentTimeline0_ + 1};
    else if (length < mid) return Vector{currentTimeline0_ - length - 1, length - currentTimeline0_};
    else return Vector{- currentTimeline0_, currentTimeline0_};
}

void Universe::setPresent(int p) {
    present_ = p;
}

int Universe::getPresent() const {
    return present_;
}

std::shared_ptr<Universe> Universe::clone() const {
    auto newUniverse = std::make_shared<Universe>();
    for (int x = 0; x < getTimelineCount() - currentTimeline0_; x++) {
        std::shared_ptr<Timeline> timeline = getTimeline(x);
        auto newTimeline = timeline->clone();
        newUniverse->addTimeline(newTimeline, true);
    }
    for (int x = -1; x > -currentTimeline0_ - 1; x--) {
        std::shared_ptr<Timeline> timeline = getTimeline(x);
        auto newTimeline = timeline->clone();
        newUniverse->addTimeline(newTimeline, false);
    }
    return newUniverse;
}


