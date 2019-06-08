#include "tcpconnections.h"

#define cout qDebug()

TcpConnections::TcpConnections(QObject *parent) : QObject(parent)
{
    cout<<this << " Created.";
}

size_t TcpConnections::mCountFunction() const
{
    QReadWriteLock lock;
    lock.lockForRead();
    size_t value = _mConnection.count();
    lock.unlock();
    return value;
}

void TcpConnections::_mRemoveSocketFunction(QTcpSocket *socket)
{
    if(socket == nullptr) return;
    if(!_mConnection.contains(socket)) return;

	if(socket->isOpen())
    {
        socket->disconnect();
        socket->close();
    }

    _mConnection.remove(socket);

	socket->deleteLater();

	cout << this << "clients: "<<_mConnection.size();
}

void TcpConnections::disconnected()
{
    if(!sender()) return;

    QTcpSocket * sck = static_cast<QTcpSocket*>(sender());
    if(!sck) return;
	emit releaseID(_mConnection.value(sck)->id);
    _mRemoveSocketFunction(sck);
}

void TcpConnections::error(QAbstractSocket::SocketError sckErr)
{
    if(!sender()) return;

    QTcpSocket * sck = static_cast<QTcpSocket*>(sender());
    if(!sck) return;

    _mRemoveSocketFunction(sck);
}

void TcpConnections::datasInside()
{
    TcpConnection * con =  static_cast<TcpConnection*>(sender());
	mTagData.push_back(QPair<TcpConnection* , QByteArray>(con,  con->mLastData));
    emit freshData();
}

void TcpConnections::start() {}

void TcpConnections::quit()
{
    if(!sender()) return;

    for(auto var = _mConnection.begin(); var != _mConnection.end(); var++)
    {
        _mRemoveSocketFunction(var.key());
    }

    emit finished();
}

void TcpConnections::accept(qintptr handle, TcpConnection *connection)
{
    QTcpSocket * sck = new QTcpSocket(this);

    if(!sck->setSocketDescriptor(handle))
    {
        connection->deleteLater();
        return;
    }

    connect(connection, &TcpConnection::avaiableData, this, &TcpConnections::datasInside);
    connect(sck, &QTcpSocket::disconnected, this, &TcpConnections::disconnected);
    connect(sck, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &TcpConnections::error);

    connection->moveToThread(QThread::currentThread());
    connection->mSetSocketFunction(sck);

    _mConnection.insert(sck, connection);

    emit sck->connected();
}
