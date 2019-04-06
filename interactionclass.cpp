#include "interactionclass.h"
#include "bilibilitaskclass.h"
#include "huyataskclass.h"
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
       bilibili->setStatus("正在录播");
       bilibili->getLiveUrl();
       bilibili->Start();
   }
   else if(url.contains("huya"))
   {
       HuyaTaskClass *huya=new HuyaTaskClass();
       liveTaskList.append(huya);
       huya->setFileName(fileName);
       huya->setFilePath(filePath);
       huya->setUrl(url);
       huya->setStatus("正在录播");
       huya->setPlatform("虎牙直播");
       huya->Start();
   }

}

void InteractionClass::stopTask(const QString &value)
{
    for (int i=0;i<liveTaskList.length();++i)
    {

        if(liveTaskList.at(i)->getFileName()==value)
        {
            QString platform=liveTaskList.at(i)->getPlatform();
            if(platform=="bilibili"||platform=="huya")
            {
                liveTaskList.at(i)->setStatus("暂停");
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
            QString platform=liveTaskList.at(i)->getPlatform();
            if(platform=="bilibili"||platform=="huya")
            {
                liveTaskList.at(i)->setStatus("正在录播");
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
            jb.insert("statusText",liveTaskList.at(i)->getStatus());
            QJsonDocument d;
            d.setObject(jb);
            array.append(QString(d.toJson()));
        }
        text=QJsonDocument(array).toJson();
        //qDebug()<<text;
        emit slot_upData(text);
    }
}
