#pragma once

#include <vector>
#include <memory>
#include "Timeline.h"

class Universe {
public:
    Universe();
    ~Universe();

    std::shared_ptr<Piece> returnNotFound() const;

    void addTimeline(const std::shared_ptr<Timeline> timeline);

    std::shared_ptr<Timeline> getTimeline(int index) const;

    int getTimelineCount() const;

    std::shared_ptr<Piece> getPiece(Vector xyzw) const;

private:
    std::vector<std::shared_ptr<Timeline>> timelines_;
    std::shared_ptr<Piece> notfound_;
};
