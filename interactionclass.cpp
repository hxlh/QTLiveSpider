#include "interactionclass.h"
#include "bilibilitaskclass.h"
InteractionClass::InteractionClass(QObject *parent) : QObject(parent)
{
    timer=new QTimer();
    connect(timer,&QTimer::timeout,this,&InteractionClass::UpData);
    timer->setInterval(1000);
    timer->start();
}

void InteractionClass::addTask(const QString &value)
{
   QStringList valueList =value.split(",");
   QString url=valueList.at(0);
   QString fileName=valueList.at(1);
   QString filePath=valueList.at(2);

   if(url.contains("bilibili"))
   {
       BilibiliTaskClass *bilibili=new  BilibiliTaskClass();
       liveTaskList.append(bilibili);
       bilibili->setFileName(fileName);
       bilibili->setFilePath(filePath);
       bilibili->setUrl(url);
       bilibili->setPlatform("bilibili");
       bilibili->getLiveUrl();
       bilibili->Start();
   }

}

void InteractionClass::stopTask(const QString &value)
{
    for (int i=0;i<liveTaskList.length();++i)
    {

        if(liveTaskList.at(i)->getFileName()==value)
        {
            if(liveTaskList.at(i)->getPlatform()=="bilibili")
            {
                liveTaskList.at(i)->setStopMark(true);
            }
        }
    }
}

void InteractionClass::continueTask(const QString &value)
{
    for (int i=0;i<liveTaskList.length();++i)
    {
        if(liveTaskList.at(i)->getFileName()==value)
        {
            if(liveTaskList.at(i)->getPlatform()=="bilibili")
            {
                liveTaskList.at(i)->setStopMark(false);
                liveTaskList.at(i)->Start();
            }
        }
    }
}

void InteractionClass::deleteTask(const QString &value)
{
    for (int i=0;i<liveTaskList.length();++i) {
        if(liveTaskList.at(i)->getFileName()==value)
        {
            liveTaskList.at(i)->setStopMark(true);
            delete  liveTaskList.takeAt(i);
        }
    }
}

void InteractionClass::stopTimer()
{
    timer->stop();
}

void InteractionClass::continueTimer()
{
    timer->start();
}

void InteractionClass::UpData()
{
    if(liveTaskList.length()>0)
    {
        QString text;
        QJsonArray array;
        for(int i=0;i<liveTaskList.length();++i)
        {
            QJsonObject jb;
            jb.insert("fileNameText",liveTaskList.at(i)->getFileName());
            jb.insert("totalSizeText",liveTaskList.at(i)->getTotalData());
            jb.insert("speedText",liveTaskList.at(i)->getDownSpeed());
            jb.insert("platformText",liveTaskList.at(i)->getPlatform());
            jb.insert("statusText","ok");
            QJsonDocument d;
            d.setObject(jb);
            array.append(QString(d.toJson()));
        }
        text=QJsonDocument(array).toJson();
        //qDebug()<<text;
        emit slot_upData(text);
    }
}
