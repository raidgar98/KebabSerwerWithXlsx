#pragma once

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QThread>
#include <QMap>
#include <QReadWriteLock>
#include <QQueue>

#include "tcpconnection.h"

//This class takes responsibilty for storing tcpconnections, forwarding data setting connections (QObject::connect) from connections (tcpconnection) to tcpserwer
class TcpConnections : public QObject
{
    Q_OBJECT
public:

	//Auto-generated constructor
    explicit TcpConnections(QObject *parent = nullptr);

	//Returns amount of currently active connctions
	virtual size_t mCountFunction() const;

	//Queue of readed data with TcpConnection name tag
	QQueue<QPair<TcpConnection*, QByteArray> > mTagData;

protected:

	//Core of this application -> List of all connections
    QMap<QTcpSocket*, TcpConnection*> _mConnection;

	//Methode for safety removing connection
	void _mRemoveSocketFunction(QTcpSocket * socket);

signals:

	//Signal emitted when server is closed (button 'stop' clicked)
    void quitting();

	//Signal emitted when all connections are closed
    void finished();

	//Signal emitted when new data arrived
    void freshData();

	//Signal emitted to inform that id is free (ex: if we had reserved 1, 2 and 3, and 2'nd connection were closed, thanks to this mechanism, next connection will get id=2, not 4)
	void releaseID(quint8 ID);

protected slots:

	//Slot activated when client or server want to end session
    void disconnected();

	//Slot activated when error occur
    void error(QAbstractSocket::SocketError sckErr);

	//Slot activated to inform new data arrived
    void datasInside();

public slots:

	//[Log only] Informs about starting new thread
    void start();

	//Close Connection
    void quit();

	//Accepts, set and add to new thread. Core methode
    void accept(qintptr handle, TcpConnection * connection);

};
