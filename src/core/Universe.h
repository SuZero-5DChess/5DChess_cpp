#pragma once

#include <vector>
#include <memory>
#include "Timeline.h"

class Universe {
public:
    Universe();
    ~Universe();

    void addTimeline(const Timeline& timeline);

    Timeline getTimeline(int index) const;

    int getTimelineCount() const;

private:
    std::vector<Timeline> timelines_;
};
