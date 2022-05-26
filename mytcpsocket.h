#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>       // QT += network
#include <QAbstractSocket>  // ^ in .pro
#include <QDebug>
#include <QString>

// https://www.bogotobogo.com/cplusplus/sockets_server_client.php

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = 0);

    bool doConnect();

    //void write(QString message);

private:
    char* toChar(QString _data);

signals:

public slots:

    //bool connectToHost(QString host);
    //bool writeData(QByteArray data);

    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

    void write(QString _data);

private:
    QTcpSocket *socket;
    bool VOICE = true; // false for console-silent mode

    QString SERVER_IP = "192.168.0.178";
    qint16 PORT = 5051;
    qint8 HEADER = 64;

    QString DISCONNECT_MSG = "!DISCONNECT";

};


#endif // MYTCPSOCKET_H
