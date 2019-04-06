#include "bilibilitaskclass.h"

BilibiliTaskClass::BilibiliTaskClass()
{

}
QString BilibiliTaskClass::getRoomId()
{

    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:65.0) Gecko/20100101 Firefox/65.0");//这两条必须有否则html返回出错
    req.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute,true);
    reply=manager.get(req);
    QEventLoop loop;
    connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    QString html=reply->readAll();
    delete reply;
    reply=nullptr;
    int start=html.indexOf("\"room_id\":")+QString("\"room_id\":").length();
    int length=html.indexOf(",\"short_id")-start;
    return html.mid(start,length);
}
void BilibiliTaskClass::getLiveUrl()
{
    QString roomid=getRoomId();
    QNetworkRequest req;
    req.setUrl(QUrl("https://api.live.bilibili.com/room/v1/Room/playUrl?cid="+roomid+"&quality=4&platform=web"));
    req.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:65.0) Gecko/20100101 Firefox/65.0");//这两条必须有否则html返回出错
    req.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    reply=manager.get(req);
    QEventLoop loop;
    connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    QByteArray html=reply->readAll();
    delete reply;
    reply=nullptr;
    QJsonDocument d=QJsonDocument::fromJson(html);
    QJsonObject jb=d.object();
    QJsonArray ja=jb.take("data").toObject().take("durl").toArray();
    url=ja.first().toObject().take("url").toString();
}

void BilibiliTaskClass::Start()
{
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:65.0) Gecko/20100101 Firefox/65.0");//这两条必须有否则html返回出错
    reply=manager.get(req);//因之前已delete reply 所以要先赋值给reply再进行connect
    connect(reply,&QNetworkReply::readyRead,this,&BilibiliTaskClass::slotSaveFile);
    connect(reply,&QNetworkReply::finished,this,&BilibiliTaskClass::slotDownFinished);
    QString temp=filePath+"/"+fileName+".live";
    file=new QFile(temp);//创建文件
    FILE *pf=fopen(temp.toLocal8Bit().data(),"ab+");//filePath+"/"+fileName+".live"
    file->open(pf,QIODevice::WriteOnly |QIODevice::Append,QFileDevice::AutoCloseHandle);
    //使用C语言file指针打开文件,因为QFile.close()只是刷新缓冲区并不会关闭系统底层file句柄，使用File*的方式可以及时关闭(好像没用)
}
void BilibiliTaskClass::slotSaveFile()
{
    QByteArray data=reply->readAll();
    totalData+=data.length();
    oneSecondData+=data.length();
    file->write(data);
    if(stopMark)
    {
        disconnect(reply,&QNetworkReply::readyRead,this,&BilibiliTaskClass::slotSaveFile);
        disconnect(reply,&QNetworkReply::finished,this,&BilibiliTaskClass::slotDownFinished);
        delete reply;
        reply=nullptr;
        file->close();
        delete file;
        file=nullptr;
    }
}
void BilibiliTaskClass::slotDownFinished()
{
    delete reply;
    reply=nullptr;
    file->close();
    delete file;
    file=nullptr;
}
