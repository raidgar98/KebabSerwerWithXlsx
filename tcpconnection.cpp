#include "tcpconnection.h"

#define cout qDebug()

TcpConnection::TcpConnection(QObject *parent) : QObject(parent) {}

TcpConnection::~TcpConnection() {}

void TcpConnection::mSetSocketFunction(QTcpSocket *socket)
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
	if(mIsReadyRead)
	{
		mIsReadyRead = false;
		_mSocket->write(src);
		_mSocket->waitForBytesWritten();
		//mGetSocketFunction()->flush();
	}
}

QTcpSocket * const TcpConnection::mGetSocketFunction()
{
	if(!sender()) return nullptr;

	return static_cast<QTcpSocket * const>(sender());
}

void TcpConnection::connected() { if(!sender()) return; }

void TcpConnection::disconnected() { if(!sender()) return; }

void TcpConnection::bytesWritten(qint64 bytes) { if(!sender()) return; }

void TcpConnection::statesChanged(QAbstractSocket::SocketState socketState) { if(!sender()) return; }

void TcpConnection::error(QAbstractSocket::SocketError sockError) {	if(!sender()) return; }

void TcpConnection::readyRead()
{
	if(!sender()) return;
	mLastData = mGetSocketFunction()->readAll();
	QByteArray data(mLastData);

	if(data == "^\r\n")
	{
		emit _mSocket->disconnected();
		emit avaiableData();
		return;

	}else if (data == "hello server \r\n\r\n\r\n")
	{
		mLastData = "^&\r\n";
	}

	mIsReadyRead = true;
	emit avaiableData();
}
