#include "mytcpsocket.h"

#include <iostream>

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{
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
        if ( VOICE ) qDebug() << "Error: " << socket->errorString();
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

void MyTcpSocket::readyRead()
{
    if ( VOICE ) qDebug() << "reading...";
    if ( VOICE ) qDebug() << socket->readAll();
}

char* MyTcpSocket::toChar(QString _data){
    const QByteArray stringData = _data.toUtf8();
    char* data = new char[stringData.size()];
    std::copy(stringData.constBegin(),stringData.constBegin()+stringData.size(),data);
    return data;
}

void MyTcpSocket::write(QString _data){
    QString _n = QString::number(_data.size());
    _n += QString(" ").repeated(HEADER-_n.size());
    socket->write(_n.toUtf8());
    socket->write(_data.toUtf8());
}
