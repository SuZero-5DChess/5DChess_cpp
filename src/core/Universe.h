#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "Timeline.h"

class Universe {
public:
    Universe();
    ~Universe();

    std::shared_ptr<Piece> returnNotFound() const;

    void addTimeline(const std::shared_ptr<Timeline> timeline, bool isPositive);
    std::shared_ptr<Timeline> getTimeline(int index) const;
    int getTimelineCount() const;

    void setPiece(Vector xyzw, std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> getPiece(Vector xyzw) const;

    void addCrossBlankPiece(Vector piece, Vector zw);

private:
    std::vector<std::shared_ptr<Timeline>> timelines_;
    std::shared_ptr<Piece> notfound_;
    std::unordered_map<Vector, std::vector<Vector>> crossBlankPieces_;
    int currentTimeline0_;
};
