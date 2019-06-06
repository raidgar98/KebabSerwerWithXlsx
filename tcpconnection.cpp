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
	cout << this << "Sprawdzam dostępność...";
	if(mIsReadyRead)
	{
		cout << this << "Wysyłam dane: "<< src;
		mIsReadyRead = false;
		_mSocket->write(src);
		_mSocket->waitForBytesWritten();
		cout << this << "Wysłano: "<<src;
		mGetSocketFunction()->flush();
		cout << this << "Czyszcze buffor";
	}

	//_getSocket()->waitForReadyRead();
}

QTcpSocket * const TcpConnection::mGetSocketFunction() const noexcept
{
	if(!sender()) return nullptr;

	return static_cast<QTcpSocket * const>(sender());
}

void TcpConnection::connected()
{
	if(!sender()) return;

	qDebug()<<this<<" connected "<<sender();
}

void TcpConnection::disconnected()
{
	if(!sender()) return;

	qDebug()<<this<<" disconnected "<<mGetSocketFunction();
}

void TcpConnection::bytesWritten(qint64 bytes)
{
	if(!sender()) return;

	qDebug() << this << mGetSocketFunction() << " bytes written = "<<bytes;
}

void TcpConnection::statesChanged(QAbstractSocket::SocketState socketState)
{
	if(!sender()) return;

	qDebug() << this << mGetSocketFunction() << " socket state changed to = "<<socketState;
}

void TcpConnection::error(QAbstractSocket::SocketError sockError)
{
	if(!sender()) return;

	qDebug() << this << mGetSocketFunction() << " error = "<<sockError;
}

void TcpConnection::readyRead()
{
	cout << this << "Jestem tutaj readyRead";
	if(!sender()) return;
	//while(!lastDataM.try_lock()) {;};
	mLastData = mGetSocketFunction()->readAll();
	QByteArray data(mLastData);
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
		mLastData = "^&\r\n";
	}

	mIsReadyRead = true;
	emit avaiableData();
}


