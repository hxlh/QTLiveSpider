#include "huyataskclass.h"

HuyaTaskClass::HuyaTaskClass()
{

}
void HuyaTaskClass::Start()
{
    QString theUrl=getLiveUrl();
    QNetworkRequest req;
    req.setUrl(theUrl);
    reply=manager.get(req);//因之前已delete reply 所以要先赋值给reply再进行connect
    connect(reply,&QNetworkReply::readyRead,this,&HuyaTaskClass::slotSaveFile);
    connect(reply,&QNetworkReply::finished,this,&HuyaTaskClass::slotDownFinished);
    file=new QFile(filePath+"/"+fileName+".live");
    file->open(QIODevice::WriteOnly |QIODevice::Append);

}
QString HuyaTaskClass::getLiveUrl()
{
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    reply=manager.get(req);
    QEventLoop loop;
    connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    QByteArray html=reply->readAll();
    delete reply;
    reply=nullptr;
    //获取前缀
    int startFlvUrl=html.indexOf("sFlvUrl\":\"")+10;
    int lengthFlvUrl=html.indexOf("\",\"sFlvUrlSuffix",startFlvUrl)-startFlvUrl;
    QString flvUrl=html.mid(startFlvUrl,lengthFlvUrl).replace("\\/","/");
    //
    //获取28503864-28503864-122423163689631744-3104089158-10057-A-0-1
    int startStreamName=html.indexOf("sStreamName\":\"")+QString("sStreamName\":\"").length();
    int lengthStreamName=html.indexOf("\",\"sFlvUrl")-startStreamName;
    QString streamName=html.mid(startStreamName,lengthStreamName);
    //
    //获取wsSecret
    int startWsSecret=html.indexOf("wsSecret");
    int lengthWsSecret=html.indexOf("\",\"sHlsUrl")-startWsSecret;
    QString wsSecret=html.mid(startWsSecret,lengthWsSecret);
    //
    QString result= flvUrl+"/"+streamName+".flv?"+wsSecret;
    return result;
}

void HuyaTaskClass::slotSaveFile()
{
    QByteArray data=reply->readAll();
    totalData+=data.length();
    oneSecondData+=data.length();
    file->write(data);
    if(stopMark)
    {
        disconnect(reply,&QNetworkReply::readyRead,this,&HuyaTaskClass::slotSaveFile);
        disconnect(reply,&QNetworkReply::finished,this,&HuyaTaskClass::slotDownFinished);
        delete reply;
        reply=nullptr;
        file->close();
        delete file;
        file=nullptr;
    }
}

void HuyaTaskClass::slotDownFinished()
{
    delete reply;
    reply=nullptr;
    file->close();
    delete file;
    file=nullptr;
}
