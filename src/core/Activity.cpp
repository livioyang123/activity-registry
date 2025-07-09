//
// Created by 39347 on 09/07/2025.
//
#include "core/Activity.h"

Activity::Activity(int id, const std::string& desc,
                   const std::chrono::system_clock::time_point& start,
                   const std::chrono::system_clock::time_point& end)
    : id(id), description(desc), startTime(start), endTime(end) {}

std::chrono::duration<double> Activity::getDuration() const {
    return endTime - startTime;
}

bool Activity::isValid() const {
    return endTime > startTime && !description.empty();
}
