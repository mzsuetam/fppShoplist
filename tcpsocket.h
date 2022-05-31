#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>       // QT += network
#include <QAbstractSocket>  // ^ in .pro
#include <QDebug>
#include <QString>
#include <QThread>

#define D_PORT 5050
#define D_HEADER 64

#define CONNECTION_MESSAGES QString DISCONNECT_MSG = "!DISCONNECT";\
QString VALIDATE_CONNECTION_MSG = "!VALIDATEFPP";\
QString INCOMING_DATA_MSG = "!INCOMING_DATA";


// https://www.bogotobogo.com/cplusplus/sockets_server_client.php

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket();
    explicit TcpSocket(QString ip);
    ~TcpSocket();

    bool isConnected()const{ return is_connected; }

    QString searchLocalForHost(); // search for host in local network

    QString read(bool& recieved) const; // read data

    void write(QString _data) const; // send data

    void writeDisconnectMsg(){ write( DISCONNECT_MSG);}
    void writeValidateMsg(){ write(VALIDATE_CONNECTION_MSG);}
    void writeDataMsg(){ write(INCOMING_DATA_MSG);}

signals:

public slots:

    void connected(); // unused
    void disconnected(); // unused
    void bytesWritten(qint64 bytes); // unused
    void readyRead();

private:
    QTcpSocket *socket;
    bool is_connected = false;

    bool VOICE = false; // false for console-silent mode

    QString SERVER_IP;
    qint16 PORT = D_PORT;
    qint8 HEADER = D_HEADER;

    CONNECTION_MESSAGES

public:
    static const int CONNECTION_WAITING_TIME = 5000;
    static const int READING_WAITING_TIME = 2000;
};

class SimpleTcpSocket : public QThread
{
    Q_OBJECT
public:

    explicit SimpleTcpSocket(QString IP);

    void run(); // initialised by QThread::start()

    QString read(bool& recieved);

    void write(QString _data);

    QString getServerIp(){ return SERVER_IP; }

signals:

public slots:

    void readyRead(){}

private:
    QTcpSocket *socket;
    bool VOICE = false; // false for console-silent mode


    QString SERVER_IP;
    qint16 PORT = D_PORT;
    qint8 HEADER = D_HEADER;

    CONNECTION_MESSAGES

public:
    static const int CONNECTION_WAITING_TIME = 2000;
};

#endif // TCPSOCKET_H
