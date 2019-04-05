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
    void UpData();
    QList<LiveTaskClass*> liveTaskList;
signals:
    void slot_upData(QString result);
public slots:
};

#endif // INTERACTIONCLASS_H
