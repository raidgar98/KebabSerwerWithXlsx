#ifndef TCPCONNECTIONS_H
#define TCPCONNECTIONS_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QThread>
#include <QMap>
#include <QReadWriteLock>
#include <QQueue>

#include "tcpconnection.h"

//Klasa zajmująca się składowaniem wszystkich połączeń, przekazywaniem danych oraz ustanawianiem połączeń między poszczególnymi połączeniami a klasą tcpSerwer
class TcpConnections : public QObject
{
    Q_OBJECT
public:

	//Konstruktor z śłowem kluczowym explicit
    explicit TcpConnections(QObject *parent = nullptr);

	//Metoda zwracająca ilość aktuanych połączeń
	virtual size_t count() const;

	//Kolejka odebranych danych, wraz z odbiorcą
	QQueue<QPair<TcpConnection*, QByteArray> > dataQueue;

protected:

	//Spis wszystkich połączeń (rdzeń klasy)
    QMap<QTcpSocket*, TcpConnection*> _mConnection;

	//Metoda do bezpiecznego usuwania połączeń
    void removeSocket(QTcpSocket * socket);

signals:

	//Sygnał podnoszony w momencie zamykania (stopowania) serwera
    void quitting();

	//Sygnał podnoszony po finalizacji procesu zamykania (gdy wszystki połączenia zostały zamknięte i usunięte)
    void finished();

	//Sygnał podnoszony, gdy przybyły nowe dane
    void freshData();

	//Sygnał oznajmiający zwolnienie ID (gdy mamy zajęte ID 1 2 i 3, a odepnie się 2, to żeby to było kolejne ID, jakie zostanie przydzielone)
	void releaseID(quint8 ID);

protected slots:

	//Slot aktywowany gdy połączenie 'wyraża chęć' zakończenia, lub wymaga usunięcia
    void disconnected();

	//Slot aktywowany w momencie pojawienia się błędu na gnieździe
    void error(QAbstractSocket::SocketError sckErr);

	//Slot odpowiedzialny za informowanie o przybyciu świerzych danych
    void datasInside();

public slots:

	//Informuje o rozpoczęciu nowego połączeniu na nowym wątku
    void start();

	////amyka wszystkie połączenia
    void quit();

	//Akceptuje, ustawia, konfiguruje i daje do nowego wątku nowe połączenia
    void accept(qintptr handle, TcpConnection * connection);


};

#endif // TCPCONNECTIONS_H
