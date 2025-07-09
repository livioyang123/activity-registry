#ifndef ACTIVITYWINDOW_H
#define ACTIVITYWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QListWidget>
#include <QPushButton>
#include <chrono>
#include "core/Registry.h"
#include "core/Activity.h"

class ActivityWindow : public QMainWindow
{
    Q_OBJECT

public:
    ActivityWindow(QWidget *parent = nullptr);
    ~ActivityWindow();

private slots:
    void onAddActivity();
    void onDeleteActivity();
    void onDateChanged();

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QDateEdit *dateEdit;
    QListWidget *activityList;
    QPushButton *addButton;
    QPushButton *deleteButton;

    Registry registry;
    int nextActivityId;

    void updateActivityList();
    QString activityToString(const Activity& activity) const;
    std::chrono::system_clock::time_point parseTimeString(const QString& timeStr, const QDate& date) const;
    QString formatTimePoint(const std::chrono::system_clock::time_point& timePoint) const;
    QString formatDuration(const std::chrono::duration<double>& duration) const;
    int getNextActivityId();
};

#endif // ACTIVITYWINDOW_H