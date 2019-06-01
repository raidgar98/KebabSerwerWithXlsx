#ifndef TCPSERWER_H
#define TCPSERWER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QThread>
#include "tcpconnections.h"
#include "tcpconnection.h"

#include <array>

class IDManager : public QObject
{
	Q_OBJECT;

	std::array<bool, 10> __mAvaiableIDs = {false, false, false, false, false,false, false, false, false, false};

	bool __validate(const quint8 id) const noexcept;

public:

	void release(const quint8 id) noexcept;
	bool isFree(const quint8 id) const noexcept;
	bool reserve(const quint8 id) noexcept;
	quint8 getNew() noexcept;

public slots:

	void releaseSlot(quint8 ID);

};

class TCPSerwer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPSerwer(QObject *parent = nullptr);
    ~TCPSerwer();

    virtual bool listen(const QHostAddress &address, quint16 port = 12345);
    virtual void close();
    virtual qint16 port();

	IDManager manager;

	QQueue<QPair<TcpConnection *, QByteArray> > dataQueueRead;
	//QQueue<QPair<TcpConnection *, QByteArray> > dataQueueWrite;


protected:

    QThread * _mThread = nullptr;
    TcpConnections * _mConnections = nullptr;
    virtual void incomingConnection(qintptr decriptor);
    virtual void accept(qintptr descriptor, TcpConnection * conn);

signals:

    void accepting(qintptr handle, TcpConnection * conn);
    void finished();
    void avaiableRead();


public slots:

    void complete();
    void freshDataArrive();

};

#endif // TCPSERWER_H
