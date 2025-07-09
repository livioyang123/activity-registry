//
// Created by 39347 on 09/07/2025.
//

#pragma once
#include <string>
#include <chrono>

class Activity {
private:
    int id;
    std::string description;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;

public:
    Activity(int id, const std::string& desc,
             const std::chrono::system_clock::time_point& start,
             const std::chrono::system_clock::time_point& end);

    // Getters
    int getId() const { return id; }
    std::string getDescription() const { return description; }
    std::chrono::system_clock::time_point getStartTime() const { return startTime; }
    std::chrono::system_clock::time_point getEndTime() const { return endTime; }

    // Metodi utility
    std::chrono::duration<double> getDuration() const;
    bool isValid() const;
};

