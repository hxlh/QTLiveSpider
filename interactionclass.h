#ifndef INTERACTIONCLASS_H
#define INTERACTIONCLASS_H

#include <QObject>
#include "bilibilitaskclass.h"

class InteractionClass : public QObject
{
    Q_OBJECT
public:
    explicit InteractionClass(QObject *parent = nullptr);
    Q_INVOKABLE void addTask(const QString &value);
    Q_INVOKABLE void stopTask(const QString &value);
    Q_INVOKABLE void continueTask(const QString &value);
    Q_INVOKABLE void deleteTask(const QString &value);
    Q_INVOKABLE void stopTimer();
    Q_INVOKABLE void continueTimer();
    void UpData();
    QList<LiveTaskClass*> liveTaskList;
    QTimer *timer;
signals:
    void slot_upData(QString result);
public slots:
};

#endif // INTERACTIONCLASS_H
