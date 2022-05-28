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

    ~MyTcpSocket();

    bool doConnect(QString ip);

    QString searchLocalForHost();

    QString read(bool& recieved);

    void write(QString _data);

signals:

public slots:


    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();


private:
    QTcpSocket *socket;
    bool VOICE = false; // false for console-silent mode

    // QString SERVER_IP; // "192.168.0.178";
    qint16 PORT = 5050;
    qint8 HEADER = 64;

    QString DISCONNECT_MSG = "!DISCONNECT";

};


#endif // MYTCPSOCKET_H
