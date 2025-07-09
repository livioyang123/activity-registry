//
// Created by 39347 on 09/07/2025.
//
#pragma once

#include <QDate>
#include <QMap>
#include <QList>
#include <QString>
#include "Activity.h"

class Registry {
public:
    Registry();
    ~Registry();

    void addActivity(const QDate& date, const Activity& activity);

    QList<Activity> getActivities(const QDate& date) const;
    QList<Activity> getAllActivities() const;

    // Metodi per rimuovere attività
    bool removeActivity(const QDate& date, int activityId);
    bool removeAllActivities(const QDate& date);

private:
    QMap<QDate, QList<Activity>> activitiesByDate;
};