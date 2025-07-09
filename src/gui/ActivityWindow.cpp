#include "gui/ActivityWindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>
#include <chrono>


ActivityWindow::ActivityWindow(QWidget *parent)
    : QMainWindow(parent), nextActivityId(1)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    dateEdit = new QDateEdit(QDate::currentDate(), this);
    activityList = new QListWidget(this);
    addButton = new QPushButton("Aggiungi Attività", this);
    deleteButton = new QPushButton("Elimina Attività", this);

    layout->addWidget(dateEdit);
    layout->addWidget(activityList);
    layout->addWidget(addButton);
    layout->addWidget(deleteButton);

    connect(addButton, &QPushButton::clicked, this, &ActivityWindow::onAddActivity);
    connect(deleteButton, &QPushButton::clicked, this, &ActivityWindow::onDeleteActivity);
    connect(dateEdit, &QDateEdit::dateChanged, this, &ActivityWindow::onDateChanged);

    setWindowTitle("Registro Attività");
    resize(400, 300);

    // Carica le attività per la data corrente
    updateActivityList();
}

ActivityWindow::~ActivityWindow() {}

void ActivityWindow::onAddActivity() {
    bool ok;

    QString descrizione = QInputDialog::getText(this, tr("Aggiungi attività"),
                                                tr("Descrizione attività:"), QLineEdit::Normal,
                                                "", &ok);
    if (!ok || descrizione.isEmpty())
        return;

    QString oraInizio = QInputDialog::getText(this, tr("Orario inizio"),
                                              tr("Inserisci orario inizio (HH:mm):"), QLineEdit::Normal,
                                              "09:00", &ok);
    if (!ok || oraInizio.isEmpty())
        return;

    QString oraFine = QInputDialog::getText(this, tr("Orario fine"),
                                            tr("Inserisci orario fine (HH:mm):"), QLineEdit::Normal,
                                            "10:00", &ok);
    if (!ok || oraFine.isEmpty())
        return;

    // Validazione degli orari
    QTime startTime = QTime::fromString(oraInizio, "HH:mm");
    QTime endTime = QTime::fromString(oraFine, "HH:mm");

    if (!startTime.isValid() || !endTime.isValid()) {
        QMessageBox::warning(this, tr("Errore"), tr("Formato orario non valido. Utilizzare HH:mm"));
        return;
    }

    if (startTime >= endTime) {
        QMessageBox::warning(this, tr("Errore"), tr("L'orario di fine deve essere successivo all'orario di inizio"));
        return;
    }

    // Converti gli orari in time_point
    QDate selectedDate = dateEdit->date();
    auto startTimePoint = parseTimeString(oraInizio, selectedDate);
    auto endTimePoint = parseTimeString(oraFine, selectedDate);

    // Crea l'oggetto Activity
    Activity newActivity(getNextActivityId(), descrizione.toStdString(), startTimePoint, endTimePoint);

    if (!newActivity.isValid()) {
        QMessageBox::warning(this, tr("Errore"), tr("Attività non valida"));
        return;
    }

    // Aggiungi l'attività al registry
    registry.addActivity(selectedDate, newActivity);

    // Aggiorna la lista
    updateActivityList();
}

void ActivityWindow::onDeleteActivity() {
    QListWidgetItem *item = activityList->currentItem();
    if (!item) {
        QMessageBox::warning(this, tr("Elimina Attività"), tr("Seleziona un'attività da eliminare."));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Conferma eliminazione"),
                                  tr("Sei sicuro di voler eliminare l'attività selezionata?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QDate selectedDate = dateEdit->date();
        QList<Activity> activities = registry.getActivities(selectedDate);

        int currentRow = activityList->currentRow();
        if (currentRow >= 0 && currentRow < activities.size()) {
            // Rimuovi l'attività dal registry usando l'ID
            registry.removeActivity(selectedDate, activities[currentRow].getId());

            // Aggiorna la lista
            updateActivityList();
        }
    }
}

void ActivityWindow::onDateChanged() {
    updateActivityList();
}

void ActivityWindow::updateActivityList() {
    QDate selectedDate = dateEdit->date();
    activityList->clear();

    QList<Activity> activities = registry.getActivities(selectedDate);

    // Ordina le attività per orario di inizio
    std::sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.getStartTime() < b.getStartTime();
    });

    for (const Activity& activity : activities) {
        QString itemText = activityToString(activity);
        activityList->addItem(itemText);
    }
}

QString ActivityWindow::activityToString(const Activity& activity) const {
    QString description = QString::fromStdString(activity.getDescription());
    QString startTime = formatTimePoint(activity.getStartTime());
    QString endTime = formatTimePoint(activity.getEndTime());
    QString duration = formatDuration(activity.getDuration());

    return QString("%1 - %2 - %3 (Durata: %4)")
        .arg(description)
        .arg(startTime)
        .arg(endTime)
        .arg(duration);
}

std::chrono::system_clock::time_point ActivityWindow::parseTimeString(const QString& timeStr, const QDate& date) const {
    QTime time = QTime::fromString(timeStr, "HH:mm");
    if (!time.isValid()) {
        return std::chrono::system_clock::time_point{};
    }

    QDateTime dateTime(date, time);
    return std::chrono::system_clock::from_time_t(dateTime.toSecsSinceEpoch());
}

QString ActivityWindow::formatTimePoint(const std::chrono::system_clock::time_point& timePoint) const {
    auto time_t = std::chrono::system_clock::to_time_t(timePoint);
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(time_t);
    return dateTime.time().toString("HH:mm");
}

QString ActivityWindow::formatDuration(const std::chrono::duration<double>& duration) const {
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - minutes);

    if (minutes.count() >= 60) {
        auto hours = std::chrono::duration_cast<std::chrono::hours>(minutes);
        minutes = std::chrono::duration_cast<std::chrono::minutes>(minutes - hours);
        return QString::number(hours.count()) + "h " + QString::number(minutes.count()) + "m";
    } else {
        return QString::number(minutes.count()) + "m";
    }
}

int ActivityWindow::getNextActivityId() {
    return nextActivityId++;
}