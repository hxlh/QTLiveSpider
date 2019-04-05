#ifndef BILIBILITASKCLASS_H
#define BILIBILITASKCLASS_H
#include "livetaskclass.h"

class BilibiliTaskClass : public LiveTaskClass
{
public:
    BilibiliTaskClass();
    virtual void Start();
    void getLiveUrl();
private:
    QString getRoomId();
public slots:
    void slotSaveFile();
    void slotDownFinished();
};

#endif // BILIBILITASKCLASS_H
