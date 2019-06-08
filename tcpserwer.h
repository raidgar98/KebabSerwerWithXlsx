#pragma once

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QThread>
#include "tcpconnections.h"
#include "tcpconnection.h"

#include <array>

//Class for managing IDs
class IDManager : public QObject
{
	Q_OBJECT

	//Array of avaiable IDs
	std::array<bool, 10> __mAvaiableIDs = {false, false, false, false, false,false, false, false, false, false};

	//Checks is ID is in range
	bool __mValidateFunction(const quint8 id) const noexcept;

public:

	//Release 'id' ID
	void mReleaseFunction(const quint8 id) noexcept;

	//Checks is 'id' is free to reserve
	bool mIsFreeFunction(const quint8 id) const noexcept;

	//Tries to reserve id, if goes well return true
	bool mReserveFunctions(const quint8 id) noexcept;

	//Get lowest avaiable id, and reserves it
	quint8 mGetNewFunction() noexcept;

public slots:

	//Slot activated to release ID by calling mReleaseFunction
	void releaseSlot(quint8 ID);

};

class TCPSerwer : public QTcpServer
{
    Q_OBJECT

public:

	//Auto-generate constructor
	explicit TCPSerwer(QObject *parent = nullptr);

	//Auto-generated destructor
    ~TCPSerwer();

	//After calling this methode serwer start working and listning
    virtual bool listen(const QHostAddress &address, quint16 port = 12345);

	//This methode close serwer by closing all connections and stopping listen
    virtual void close();

	//returns actual port
    virtual qint16 port();

	//Manages ID's
	IDManager manager;

	//Queue of read data, with TcpConnection as identificator
	QQueue<QPair<TcpConnection *, QByteArray> > dataQueueRead;

protected:

	//Holds thread
    QThread * _mThread = nullptr;

	//Holds class that is resposible for holding connections
    TcpConnections * _mConnections = nullptr;

	//Called if detected, that new connection is coming
    virtual void incomingConnection(qintptr decriptor);

	//Indicates accepting procedure
    virtual void accept(qintptr descriptor, TcpConnection * conn);

signals:

	//Emitted as request to setup connection
    void accepting(qintptr handle, TcpConnection * conn);

	//Emitted when everythink is closed
    void finished();

	//Emitted when new data arrive for mainwindow
    void avaiableRead();


public slots:

	//Called when thread is closed
    void complete();

	//Called when new data arrive from tcpconnections
    void freshDataArrive();

};
