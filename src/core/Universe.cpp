#include "Universe.h"

#include <Notfound.h>

Universe::Universe(): crossBlankPieces_(), currentTimeline0_(0), present_(0) {
    auto notfound = std::make_shared<Piece>(PieceType::NotFound, ColorType::White, nullptr);
    notfound_ = notfound;
}

Universe::~Universe() {}

std::shared_ptr<Piece> Universe::returnNotFound() const {
    return notfound_;
}


void Universe::addTimeline(const std::shared_ptr<Timeline> timeline, bool isPositive) {
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


void Universe::setPiece(Vector xyzw, std::shared_ptr<Piece> piece) {
    int x = xyzw[0];
    int y = xyzw[1];
    int z = xyzw[2];
    int w = xyzw[3];
    getTimeline(w)->getBoardState(z)->setPiece(x, y, piece);
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

void Universe::addCrossBlankPiece(Vector place, Vector zw) {
    crossBlankPieces_[zw].push_back(place);
}

void Universe::checkCrossBlankPiece(Vector zw) {
    if (crossBlankPieces_.find(zw) != crossBlankPieces_.end()) {
        for (const auto& piecePos : crossBlankPieces_[zw]) {
            std::shared_ptr<Piece> piece = getPiece(piecePos);
            piece->setValidMoves(piece->getValidMoves());
        }
    }
}

Vector<int> Universe::getActiveTimelines() {
    int length = getTimelineCount() - 1;
    int mid = 2 * currentTimeline0_;
    if (length > mid) return Vector{- currentTimeline0_, currentTimeline0_};
    else if (length < mid) return Vector{currentTimeline0_ - length, length - currentTimeline0_};
    else return Vector{- currentTimeline0_, length - currentTimeline0_};
}

void Universe::setPresent(int p) {
    present_ = p;
}

int Universe::getPresent() const {
    return present_;
}



