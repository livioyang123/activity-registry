//
// Created by 39347 on 09/07/2025.
//
#include "core/Registry.h"
#include <QDebug>

Registry::Registry() {
    // Costruttore di default
}

Registry::~Registry() {
    // Distruttore
}

void Registry::addActivity(const QDate& date, const Activity& activity) {
    if (date.isValid()) {
        activitiesByDate[date].append(activity);
    }
}

bool Registry::removeActivity(const QDate& date, const Activity& activity) {
    if (activitiesByDate.contains(date)) {
        QList<Activity>& activities = activitiesByDate[date];
        int index = activities.indexOf(activity);
        if (index != -1) {
            activities.removeAt(index);
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