//
// Created by 39347 on 09/07/2025.
//
#include <QDate>
#include <core/Activity.h>
#pragma once
class Registry {
    public:
        Registry();
        ~Registry();

    void addActivity(const QDate& date, const Activity& activity);

    bool removeActivity(const QDate& date, const Activity& activity);

    bool removeAllActivities(const QDate& date);

    private:
        QMap<QDate, QList<Activity>> activitiesByDate;
};
