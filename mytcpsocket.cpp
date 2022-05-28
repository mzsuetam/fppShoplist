#include "mytcpsocket.h"

#include <iostream>
#include <QEventLoop>
#include <QTimer>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{
}

MyTcpSocket::~MyTcpSocket(){
    write(DISCONNECT_MSG);
    if ( VOICE ) qDebug() << "socket killed";
}

bool MyTcpSocket::doConnect(QString ip)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    if ( VOICE ) qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost(ip, PORT);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        if ( VOICE ) qDebug() << "Socket Error: " << socket->errorString();
        return false;
    }

    return true;
}

QString MyTcpSocket::searchLocalForHost(){
    QString local_ip = "";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             local_ip = address.toString(); // found "xxx.xxx.x.xxx"
    }
    // @TODO:
    // should throw an exception here
    if ( local_ip == "" ) return "";
    int ptr = local_ip.lastIndexOf('.');
    local_ip = local_ip.left(ptr+1); // trim last 3
    ///
    for (int i=0; i<255; i++){ // trying to connect to all local servers
        {
        // @TODO:
        // this shit should be in threads
        //  https://www.youtube.com/watch?v=JaGqGhRW5Ks
        qDebug() << "Trying to connect to " << local_ip+QString::number(i);
        socket->connectToHost(local_ip+QString::number(i), PORT);
        if(socket->waitForConnected(1000)) // check behaviour in threadsS
        {
            // @TODO:
            // should send server sth like !VERIFY_CONNECTION
            // then read for !CONNECTION_VERIFIED
            // and if that didnt happen pass
            return local_ip+QString::number(i);
        }
        }
    }

    return "";
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
