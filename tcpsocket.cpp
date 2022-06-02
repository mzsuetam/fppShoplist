#include "tcpsocket.h"

#include <iostream>
#include <QEventLoop>
#include <QTimer>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QThread>


TcpSocket::TcpSocket()
{
    // SECTION OF INIT:
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
}

TcpSocket::TcpSocket(QString ip)
{
    // SECTION OF INIT:
    SERVER_IP = ip;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    // SECTION OF CONNECTING
    if ( VOICE ) qDebug() << "connecting to " << ip << "...";
    socket->connectToHost(ip, PORT);
    if(!socket->waitForConnected(5000))
    {
        if ( VOICE ) qDebug() << "Socket Error: " << socket->errorString();
        is_connected = false;
    }
    else{
        if ( VOICE ) qDebug() << "Socket Connected";
        is_connected =  true;
    }
}

TcpSocket::~TcpSocket(){
    write(DISCONNECT_MSG);
    if ( VOICE ) qDebug() << "socket killed";
}

QString TcpSocket::read(bool &recieved) const{
    if ( !is_connected ) return "";
    QEventLoop loop;
    auto timer = new QTimer(nullptr);
    timer->setSingleShot(true);
    connect( timer, &QTimer::timeout, &loop, &QEventLoop::quit ); // wait for READING_WAITING_TIME
    connect( socket, SIGNAL(readyRead()), &loop, SLOT(quit()) ); // or for gettin a message
    timer->start(READING_WAITING_TIME);
    loop.exec();
    if ( VOICE ) qDebug() << "Reading...";
    QString buff = socket->readAll();
    if ( VOICE ) qDebug() << buff;
    recieved = true;
    if ( buff == "" ) recieved = false;
    return buff;
}

void TcpSocket::write(QString _data) const{
    if ( !is_connected ) return;
    QString _n = QString::number(_data.size());
    _n += QString(" ").repeated(HEADER-_n.size());
    socket->write(_n.toUtf8());
    socket->write(_data.toUtf8());
}

QString TcpSocket::searchLocalForHost(){
    // getting local ip
    QString local_ip = "";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             local_ip = address.toString(); // found "xxx.xxx.x.xxx"
    }
    if ( local_ip == "" ) return "";// @TODO: should throw an exception here
    int ptr = local_ip.lastIndexOf('.');
    local_ip = local_ip.left(ptr+1); // trim last 3

    // searching
    QList<SimpleTcpSocket*> searchers;
    for (int i=0; i<255; i++){ // trying to connect to all local servers
        // creating thread based classes SimpleTcpSocket for each ip
        //  each tries to acquire connection to the host ( more about that in void SimpleTcpSocket::run() )
        //  if connected - leaves ip; if not - sets it to ""
        auto searcher = new SimpleTcpSocket(local_ip+QString::number(i));
        searchers.append(searcher);
        searcher->start();
    }

    // waiting for waiting time + controll 200ms for potential host answer
    QEventLoop loop;
    auto timer = new QTimer(this);
    timer->setSingleShot(true);
    connect( timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer->start( SimpleTcpSocket::CONNECTION_WAITING_TIME+1000 );
    loop.exec();

    // checking if we found a host
    QString searched_ip = "";
    for (int i=0; i<searchers.size(); i++){ // for each searcher we check it's ip
        if ( searchers[i]->getServerIp() != "" ) searched_ip = searchers[i]->getServerIp(); // we got our host - we save it
        delete searchers[i]; // delete rubbish
    }
    if (VOICE) qDebug() << "Found >" << searched_ip << "<";
    return searched_ip;
}

void TcpSocket::connected(){ if ( VOICE ) qDebug() << "connected...";}
void TcpSocket::disconnected(){if ( VOICE ) qDebug() << "disconnected...";}
void TcpSocket::bytesWritten(qint64 bytes){ if ( VOICE ) qDebug() << bytes << " bytes written...";}
void TcpSocket::readyRead(){ if ( VOICE ) qDebug() << "incoming data..."; }

/////////////////////////////////////////////////////////////////////////

SimpleTcpSocket::SimpleTcpSocket(QString ip){
    SERVER_IP = ip;
    socket = new QTcpSocket();

    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
}

void SimpleTcpSocket::run(){
    if ( VOICE ) qDebug() << "SimpleTcpSocket connecting to " << SERVER_IP << "...";

    // what generates ~500 red lines is below:
    socket->connectToHost(SERVER_IP, PORT); // try to connect to owned ip

    if(!socket->waitForConnected(CONNECTION_WAITING_TIME))
    {
        // if failed: set SERVER_IP to ""
        if ( VOICE ) qDebug() << "Socket Error: " << socket->errorString();
        SERVER_IP = "";
    }
    else
    {
        // if success: check if this is FppShoplist host:
        write( VALIDATE_CONNECTION_MSG );
        bool recieved;
        QString ans = read( recieved );
        if ( recieved && ans=="Connection to FppShoplist host validated!" ){ // if yes: save SERVER_IP as it is
            if ( VOICE ) qDebug() << "Socket Connected";
            ans = read( recieved );
            write( DISCONNECT_MSG );
        } // if no: set SERVER_IP to ""
        else SERVER_IP = "";
    }
}


QString SimpleTcpSocket::read(bool &recieved){
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

void SimpleTcpSocket::write(QString _data){
    QString _n = QString::number(_data.size());
    _n += QString(" ").repeated(HEADER-_n.size());
    socket->write(_n.toUtf8());
    socket->write(_data.toUtf8());
}
