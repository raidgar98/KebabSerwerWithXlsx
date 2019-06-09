#pragma once

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <mutex>


//Class responsible for handling events on socket
class TcpConnection: public QObject
{
    Q_OBJECT

public:

	//Unique ID for every connectio to make life easier
	quint8 id;

	//Informs is socket ready for reading fresh data
	bool mIsReadyRead = false;

	//Auto-generated constructor
    explicit TcpConnection(QObject *parent = nullptr);

	//Destructor
    ~TcpConnection();

	//Socket setup
	virtual void mSetSocketFunction(QTcpSocket * socket);

	//Stores last received data for future transmission to mainwindow
	QByteArray mLastData;

	//Getter for _mSocket
	QTcpSocket * const mGetSocketFunction();

protected:

	//Pointer on socket, this class working on
    QTcpSocket * _mSocket = nullptr;


public slots:

	//Slot activated if connection established correctly
    virtual void connected();

	//Slot activated if disconnected
    virtual void disconnected();

	//Slot activated if new data arrived
    virtual void bytesWritten(qint64 bytes);

	//Slot activated if sockets state changed
    virtual void statesChanged(QAbstractSocket::SocketState socketState);

	//Slot activated  if error occured
    virtual void error(QAbstractSocket::SocketError sockError);

	//Slot activated if socket is ready for reading
	virtual void readyRead();

	//Slot activated to write data (slot for mainwindow)
	void wrtieData(QByteArray src);

signals:

	//Emitted if new data arrived
    void avaiableData();

};
