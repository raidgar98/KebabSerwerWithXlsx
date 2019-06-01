#include "tcpconnection.h"

#define cout qDebug()

TcpConnection::TcpConnection(QObject *parent) : QObject(parent)
{
	qDebug()<<this<<" Created";
}

TcpConnection::~TcpConnection()
{
	qDebug()<<this<<" Destoryed";
}

void TcpConnection::setSocket(QTcpSocket *socket)
{
	if(socket == nullptr) return;

	_mSocket = socket;

	connect(_mSocket, &QTcpSocket::connected, this, &TcpConnection::connected);
	connect(_mSocket, &QTcpSocket::disconnected, this, &TcpConnection::disconnected);
	connect(_mSocket, &QTcpSocket::readyRead, this, &TcpConnection::readyRead);
	connect(_mSocket, &QTcpSocket::bytesWritten, this, &TcpConnection::bytesWritten);
	connect(_mSocket, &QTcpSocket::stateChanged, this, &TcpConnection::statesChanged);
	connect(_mSocket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &TcpConnection::error);

}

void TcpConnection::wrtieData(QByteArray src)
{
	cout << this << "Sprawdzam dostępność...";
	if(isReadyRead)
	{
		cout << this << "Wysyłam dane: "<< src;
		isReadyRead = false;
		_mSocket->write(src);
		_mSocket->waitForBytesWritten();
		cout << this << "Wysłano: "<<src;
		_getSocket()->flush();
		cout << this << "Czyszcze buffor";
	}

	//_getSocket()->waitForReadyRead();
}

QTcpSocket *TcpConnection::_getSocket()
{
	if(!sender()) return 0;

	// qDebug()<<this<<" Getting Socket";

	return static_cast<QTcpSocket*>(sender());
}

void TcpConnection::connected()
{
	if(!sender()) return;

	qDebug()<<this<<" connected "<<sender();
}

void TcpConnection::disconnected()
{
	if(!sender()) return;

	qDebug()<<this<<" disconnected "<<_getSocket();
}

void TcpConnection::bytesWritten(qint64 bytes)
{
	if(!sender()) return;

	qDebug() << this << _getSocket() << " bytes written = "<<bytes;
}

void TcpConnection::statesChanged(QAbstractSocket::SocketState socketState)
{
	if(!sender()) return;

	qDebug() << this << _getSocket() << " socket state changed to = "<<socketState;
}

void TcpConnection::error(QAbstractSocket::SocketError sockError)
{
	if(!sender()) return;

	qDebug() << this << _getSocket() << " error = "<<sockError;
}

void TcpConnection::readyRead()
{
	cout << this << "Jestem tutaj readyRead";
	if(!sender()) return;
	//while(!lastDataM.try_lock()) {;};
	lastData = _getSocket()->readAll();
	QByteArray data(lastData);
	//lastDataM.unlock();

	cout << this << "Pobrano: "<<data;

	if(data == "^\r\n")
	{
		cout << this << "wykryto zamknięcie sesji";
		emit _mSocket->disconnected();
		emit avaiableData();
		return;

	}else if (data == "hello server \r\n\r\n\r\n")
	{
		cout << this << "wykryto rozpoczęcie sesji";
		lastData = "^&\r\n";
	}

	isReadyRead = true;
	emit avaiableData();
}


