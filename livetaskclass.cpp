#include "livetaskclass.h"

LiveTaskClass::LiveTaskClass(QObject *parent) : QObject(parent)
{

}
void LiveTaskClass::setUrl(QString value)
{
    url=value;
}
void LiveTaskClass::setFileName(QString value)
{
    fileName=value;
}
void LiveTaskClass::setFilePath(QString value)
{
    filePath=value;
}
void LiveTaskClass::setPlatform(QString value)
{
    platform=value;
}
void LiveTaskClass::setStopMark(bool value)
{
    stopMark=value;
}
QString LiveTaskClass::getFileName()
{
    return fileName;
}
QString LiveTaskClass::getFilePath()
{
    return filePath;
}
QString LiveTaskClass::getUrl()
{
    return url;
}
QString LiveTaskClass::getDownSpeed()
{
    qint64 data=oneSecondData;
    oneSecondData=0;
    if(data>1024 &&data<1024*1024)
    {
        return QString::number(data/1024)+"K/s";
    }else if(data>1024*1024)
    {
        return QString::number((double)(data/1024)/1024,'f',2)+"M/s";
    }else{
        return QString::number(data)+"B/s";
    }
}
QString LiveTaskClass::getTotalData()
{
    if(totalData>1024 && totalData<1024*1024)
    {
        return QString::number(totalData/1024)+"KB";
    }
    else if(totalData>1024*1024 && totalData<1024*1024*1024)
    {
        return QString::number(totalData/1024/1024)+"MB";
    }
    else if(totalData>1024*1024*1024)
    {
        return QString::number((double)(totalData/1024/1024)/1024,'f',1)+"GB";
    }else
    {
        return QString::number(oneSecondData)+"B";
    }
}
QString LiveTaskClass::getPlatform()
{
    return platform;
}
