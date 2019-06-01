#include "tcpconnections.h"

#define cout qDebug()

TcpConnections::TcpConnections(QObject *parent) : QObject(parent)
{
    cout<<this << " Created.";
}

size_t TcpConnections::count() const
{
    QReadWriteLock lock;
    lock.lockForRead();
    size_t value = _mConnection.count();
    lock.unlock();
    return value;
}

void TcpConnections::removeSocket(QTcpSocket *socket)
{
    if(socket == nullptr) return;
    if(!_mConnection.contains(socket)) return;

	if(socket->isOpen())
    {
		//cout<<this<<"removeSocket: odłączam: "<<socket;
        socket->disconnect();
        socket->close();
    }

	//cout << this << "removed.";
    _mConnection.remove(socket);

	socket->deleteLater();

	cout << this << "clients: "<<_mConnection.size();
}

void TcpConnections::disconnected()
{
    if(!sender()) return;
	//cout<<this<<" disconnecting socket: " << sender();

    QTcpSocket * sck = static_cast<QTcpSocket*>(sender());
    if(!sck) return;
	cout <<this<< "Usuwam: "<<sck;
	emit releaseID(_mConnection.value(sck)->id);
    removeSocket(sck);
	cout <<this<< "Usunięto";
}

void TcpConnections::error(QAbstractSocket::SocketError sckErr)
{
    if(!sender()) return;
	//cout<<this<< sender() << " err: "<<sckErr;

    QTcpSocket * sck = static_cast<QTcpSocket*>(sender());
    if(!sck) return;

    removeSocket(sck);
}

void TcpConnections::datasInside()
{
    TcpConnection * con =  static_cast<TcpConnection*>(sender());
	//while(!con->lastDataM.try_lock()) {;}
	dataQueue.push_back(QPair<TcpConnection* , QByteArray>(con,  con->lastData));
    emit freshData();
}

void TcpConnections::start()
{
    cout<<this<<" starting on: "<<QThread::currentThread();
}

void TcpConnections::quit()
{
    if(!sender()) return;

    cout<<this<<" Quitting...";

    for(auto var = _mConnection.begin(); var != _mConnection.end(); var++)
    {
        cout<<"Quitting socket: "<<var.key();
        removeSocket(var.key());
    }
    cout<<this<<" Quitting finished.";

    emit finished();
}

void TcpConnections::accept(qintptr handle, TcpConnection *connection)
{
    QTcpSocket * sck = new QTcpSocket(this);

    cout<<this<<" handle: "<<handle;

    if(!sck->setSocketDescriptor(handle))
    {
        qWarning()<<this<<" could not accept connection: "<<handle;
        connection->deleteLater();
        return;
    }

    connect(connection, &TcpConnection::avaiableData, this, &TcpConnections::datasInside);
    connect(sck, &QTcpSocket::disconnected, this, &TcpConnections::disconnected);
    connect(sck, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &TcpConnections::error);

    connection->moveToThread(QThread::currentThread());
    connection->setSocket(sck);

    _mConnection.insert(sck, connection);

    cout<<this << "clients = "<< _mConnection.count();

    emit sck->connected();
}

