#include "tcpserwer.h"

#define cout qDebug()

TCPSerwer::TCPSerwer(QObject *parent) : QTcpServer (parent)
{
    cout << this <<"Created on: " << QThread::currentThread();
}

TCPSerwer::~TCPSerwer()
{
    cout<<this<<"Destroyed";
}

bool TCPSerwer::listen(const QHostAddress &address, quint16 port)
{
    if(!QTcpServer::listen(address, port)) return false;

    _mThread = new QThread(this);
    _mConnections = new TcpConnections();

    connect(_mThread, &QThread::started, _mConnections, &TcpConnections::start, Qt::QueuedConnection);
    connect(this, &TCPSerwer::accepting, _mConnections, &TcpConnections::accept, Qt::QueuedConnection);
    connect(this, &TCPSerwer::finished, _mConnections, &TcpConnections::quit, Qt::QueuedConnection);
    connect(_mConnections, &TcpConnections::finished, this, &TCPSerwer::complete, Qt::QueuedConnection);
    connect(_mConnections, &TcpConnections::freshData, this, &TCPSerwer::freshDataArrive, Qt::QueuedConnection);
	connect(_mConnections, &TcpConnections::releaseID, &manager, &IDManager::releaseSlot, Qt::QueuedConnection);

    _mConnections->moveToThread(_mThread);
    _mThread->start();

    return true;

}

void TCPSerwer::close()
{
    cout << this << "Closing server";
    emit finished();
    QTcpServer::close();
}

qint16 TCPSerwer::port()
{
    if(isListening())
    {
        return this->serverPort();
    }
    else
    {
        return 12345;
    }
}

void TCPSerwer::incomingConnection(qintptr decriptor)
{
    cout<<this<<"attempt to accept connection" << decriptor;
//TO DO: IDManager TcpConnection -> TcpSerwer
    TcpConnection * conn = new TcpConnection(nullptr);

    accept(decriptor, conn);
}

void TCPSerwer::accept(qintptr descriptor, TcpConnection *conn)
{
    cout<<this<<"accepting the connection" << descriptor;
	conn->id = manager.getNew();
    conn->moveToThread(_mThread);
    emit accepting(descriptor, conn);
}

void TCPSerwer::complete()
{
    if(!_mThread)
    {
        qWarning()<<this<<" exitting complete, there was no thread";
        return;
    }

    cout<< this << "complete called, destroying thread";

    delete _mConnections;

    cout<<this<<"Quitting Thread";
    _mThread->quit();
    _mThread->wait();

    delete _mThread;

    cout<<this<<"Thread deleted";

}

void TCPSerwer::freshDataArrive()
{
	cout << this << "Data arrived";
	dataQueueRead.push_back(QPair<TcpConnection*, QByteArray>(_mConnections->mTagData.front()));
	_mConnections->mTagData.pop_front();
	emit avaiableRead();
}

bool IDManager::__validate(const quint8 id) const noexcept
{
	return id < 10;
}

void IDManager::release(const quint8 id) noexcept
{
	if(!__validate(id)) return;
	__mAvaiableIDs[id] = false;
}

bool IDManager::isFree(const quint8 id) const noexcept
{
	if(!__validate(id)) return false;
	return __mAvaiableIDs[id];
}

bool IDManager::reserve(const quint8 id) noexcept
{
	if(!__validate(id)) return false;
	if(__mAvaiableIDs[id])
		return false;
	else
	{
		__mAvaiableIDs[id] = true;
		return true;
	}
}

quint8 IDManager::getNew() noexcept
{
	for(quint8 i = 0; i < 10; i++)
	{
		if(!__mAvaiableIDs[i])
		{
			__mAvaiableIDs[i] = true;
			return i;
		}
	}

	return 254;
}

void IDManager::releaseSlot(quint8 ID)
{
	release(ID);
}
