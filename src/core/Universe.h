#pragma once

#include <unordered_map>

#include "Timeline.h"

class Universe {
public:
    Universe();
    ~Universe();

    std::shared_ptr<Piece> returnNotFound() const;

    void addTimeline(const std::shared_ptr<Timeline>& timeline, bool isPositive);
    std::shared_ptr<Timeline> getTimeline(int index) const;
    int getTimelineCount() const;
    int getCurrentTimeline0() const;

    void setPiece(const Vector& xyzw, const std::shared_ptr<Piece>& piece) const;
    std::shared_ptr<Piece> getPiece(const Vector& xyzw) const;

    Vector getActiveTimelines();

    void setPresent(int p);
    int getPresent() const;

    std::shared_ptr<Universe> clone() const;

private:
    std::vector<std::shared_ptr<Timeline>> timelines_;
    std::shared_ptr<Piece> notfound_;
    int currentTimeline0_;
    int present_;
};
