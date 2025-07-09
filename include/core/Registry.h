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

    // Metodi per aggiungere attività
    void addActivity(const QDate& date, const Activity& activity);
    void addActivities(const QDate& date, const QList<Activity>& activities);

    // Metodi per ottenere attività
    QList<Activity> getActivities(const QDate& date) const;
    QList<Activity> getAllActivities() const;
    QList<QDate> getDatesWithActivities() const;

    // Metodi per rimuovere attività
    bool removeActivity(const QDate& date, int activityId);
    bool removeActivity(const QDate& date, const Activity& activity);
    bool removeAllActivities(const QDate& date);
    void clear();

    // Metodi di controllo
    bool hasActivities(const QDate& date) const;
    bool hasActivity(const QDate& date, int activityId) const;
    bool hasActivity(const QDate& date, const Activity& activity) const;
    int getTotalActivitiesCount() const;
    int getActivitiesCount(const QDate& date) const;

    // Metodi per operazioni su range di date
    QList<Activity> getActivitiesInRange(const QDate& startDate, const QDate& endDate) const;
    QMap<QDate, QList<Activity>> getActivitiesInRangeAsMap(const QDate& startDate, const QDate& endDate) const;

    // Metodi per cercare attività per ID
    Activity* findActivityById(int id);
    const Activity* findActivityById(int id) const;

    // Operatori
    Registry& operator+=(const Registry& other);
    bool operator==(const Registry& other) const;
    bool operator!=(const Registry& other) const;

private:
    QMap<QDate, QList<Activity>> activitiesByDate;

    // Metodi privati di utilità
    void removeEmptyDates();
    bool activitiesEqual(const Activity& a, const Activity& b) const;
};