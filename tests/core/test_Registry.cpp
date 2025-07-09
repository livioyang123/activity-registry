//
// Created by 39347 on 09/07/2025.
//
#include <gtest/gtest.h>
#include <QDate>
#include "core/Registry.h"

Activity createTestActivity(int id, const std::string& desc) {
    auto now = std::chrono::system_clock::now();
    auto later = now + std::chrono::hours(1);
    return Activity(id, desc, now, later);
}

class RegistryTest : public ::testing::Test {
protected:
    Registry registry;
    QDate today = QDate::currentDate();
};

TEST_F(RegistryTest, AddAndGetActivities) {
    Activity a1 = createTestActivity(1, "Activity 1");
    Activity a2 = createTestActivity(2, "Activity 2");

    registry.addActivity(today, a1);
    registry.addActivity(today, a2);

    QList<Activity> activities = registry.getActivities(today);
    ASSERT_EQ(activities.size(), 2);

    EXPECT_EQ(activities[0].getId(), 1);
    EXPECT_EQ(activities[1].getId(), 2);
}

TEST_F(RegistryTest, GetAllActivities) {
    Activity a1 = createTestActivity(1, "Activity 1");
    Activity a2 = createTestActivity(2, "Activity 2");
    QDate otherDay = today.addDays(1);

    registry.addActivity(today, a1);
    registry.addActivity(otherDay, a2);

    QList<Activity> allActivities = registry.getAllActivities();
    ASSERT_EQ(allActivities.size(), 2);
}

TEST_F(RegistryTest, RemoveActivity) {
    Activity a1 = createTestActivity(1, "Activity 1");
    registry.addActivity(today, a1);

    bool removed = registry.removeActivity(today, 1);
    EXPECT_TRUE(removed);

    QList<Activity> activities = registry.getActivities(today);
    EXPECT_TRUE(activities.isEmpty());
}

TEST_F(RegistryTest, RemoveAllActivities) {
    Activity a1 = createTestActivity(1, "Activity 1");
    Activity a2 = createTestActivity(2, "Activity 2");
    registry.addActivity(today, a1);
    registry.addActivity(today, a2);

    bool removed = registry.removeAllActivities(today);
    EXPECT_TRUE(removed);

    QList<Activity> activities = registry.getActivities(today);
    EXPECT_TRUE(activities.isEmpty());
}