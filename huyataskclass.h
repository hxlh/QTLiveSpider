#ifndef HUYATASKCLASS_H
#define HUYATASKCLASS_H
#include "livetaskclass.h"

class HuyaTaskClass : public LiveTaskClass
{
public:
    HuyaTaskClass();
    virtual void Start();
    QString getLiveUrl();
private:

public slots:
    void slotSaveFile();
    void slotDownFinished();
};

#endif // HUYATASKCLASS_H
