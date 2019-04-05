#ifndef LIVETASKCLASS_H
#define LIVETASKCLASS_H

#include <QObject>
#include "QtNetwork"
class LiveTaskClass : public QObject
{
    Q_OBJECT
public:
    explicit LiveTaskClass(QObject *parent = nullptr);
    QString getFileName();
    QString getFilePath();
    QString getUrl();
    QString getDownSpeed();
    QString getTotalData();
    QString getPlatform();
    void setUrl(QString);
    void setFileName(QString);
    void setFilePath(QString);
    void setPlatform(QString);
    void setStopMark(bool);
    virtual  void Start()=0;
    protected:
    QString fileName="";
    QString filePath="";
    QString platform="";
    QString downSpeed="";
    QString url="";
    bool stopMark=false;
    qint64 totalData=0;
    qint64 oneSecondData=0;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QFile *file;
signals:

public slots:
};

#endif // LIVETASKCLASS_H
