//
// Created by 39347 on 09/07/2025.
//
#include <gtest/gtest.h>
#include "core/Activity.h"

class ActivityTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto now = std::chrono::system_clock::now();
        auto later = now + std::chrono::hours(1);
        activity = std::make_unique<Activity>(1, "Test Activity", now, later);
    }

    std::unique_ptr<Activity> activity;
};

TEST_F(ActivityTest, ValidActivity) {
    EXPECT_TRUE(activity->isValid());
    EXPECT_EQ(activity->getId(), 1);
    EXPECT_EQ(activity->getDescription(), "Test Activity");
}

TEST_F(ActivityTest, Duration) {
    auto duration = activity->getDuration();
    EXPECT_NEAR(duration.count(), 3600.0, 1.0);
}
