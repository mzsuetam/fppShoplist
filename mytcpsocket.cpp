#include "mytcpsocket.h"

#include <iostream>
#include <QEventLoop>
#include <QTimer>

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{
}

MyTcpSocket::~MyTcpSocket(){
    write(DISCONNECT_MSG);
    if ( VOICE ) qDebug() << "socket killed";
}

bool MyTcpSocket::doConnect()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    if ( VOICE ) qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost(SERVER_IP, PORT);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        if ( VOICE ) qDebug() << "Socket Error: " << socket->errorString();
        return false;
    }

    return true;
}

void MyTcpSocket::connected()
{
    if ( VOICE ) qDebug() << "connected...";

    // Hey server, tell me about you.
    //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void MyTcpSocket::disconnected()
{
   if ( VOICE ) qDebug() << "disconnected...";
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    if ( VOICE ) qDebug() << bytes << " bytes written...";
}

void MyTcpSocket::write(QString _data){
    QString _n = QString::number(_data.size());
    _n += QString(" ").repeated(HEADER-_n.size());
    socket->write(_n.toUtf8());
    socket->write(_data.toUtf8());
}

void MyTcpSocket::readyRead()
{
    if ( VOICE ) qDebug() << "incoming data...";
}

QString MyTcpSocket::read(bool &recieved){
    QEventLoop loop;
    auto timer = new QTimer(this);
    timer->setSingleShot(true);
    connect( timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    connect( socket, SIGNAL(readyRead()), &loop, SLOT(quit()) );
    timer->start(2000);
    loop.exec();
    if ( VOICE ) qDebug() << "Reading...";
    QString buff = socket->readAll();
    recieved = true;
    if ( buff == "" ) recieved = false;
    return buff;
}
