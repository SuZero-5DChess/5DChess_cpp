#include "Universe.h"

Universe::Universe() {}

Universe::~Universe() {}

void Universe::addTimeline(const Timeline& timeline) {
    timelines_.push_back(timeline);
}

Timeline Universe::getTimeline(int index) const {
    if (index >= 0 && index < timelines_.size()) {
        return timelines_[index];
    }
    throw -114514;
}

int Universe::getTimelineCount() const {
    return timelines_.size();
}
