
//
// Created by 39347 on 09/07/2025.
//
#include "core/Registry.h"
#include "core/Activity.h"
#include <QDebug>
#include <algorithm>

Registry::Registry() {
    // Costruttore di default
}

Registry::~Registry() {
    // Distruttore
}

void Registry::addActivity(const QDate& date, const Activity& activity) {
    if (date.isValid() && activity.isValid()) {
        activitiesByDate[date].append(activity);
    }
}


QList<Activity> Registry::getActivities(const QDate& date) const {
    return activitiesByDate.value(date, QList<Activity>());
}

QList<Activity> Registry::getAllActivities() const {
    QList<Activity> allActivities;
    for (auto it = activitiesByDate.constBegin(); it != activitiesByDate.constEnd(); ++it) {
        allActivities.append(it.value());
    }
    return allActivities;
}


bool Registry::removeActivity(const QDate& date, int activityId) {
    if (activitiesByDate.contains(date)) {
        QList<Activity>& activities = activitiesByDate[date];
        auto it = std::find_if(activities.begin(), activities.end(),
                              [activityId](const Activity& a) { return a.getId() == activityId; });
        if (it != activities.end()) {
            activities.erase(it);
            if (activities.isEmpty()) {
                activitiesByDate.remove(date);
            }
            return true;
        }
    }
    return false;
}

bool Registry::removeAllActivities(const QDate& date) {
    if (activitiesByDate.contains(date)) {
        activitiesByDate.remove(date);
        return true;
    }
    return false;
}
