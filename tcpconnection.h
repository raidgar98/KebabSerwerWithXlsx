#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <mutex>


//Klasa odpowiedzialne za obsługę zdarzeń pojawiających się na gnieździe
class TcpConnection: public QObject
{
    Q_OBJECT

public:

	//Unikalne ID każdego połączenia, celem łatwiejszej komunikacji.
	quint8 id;

	//Zmienna informująca czy gniazdo jest gotowe na odbiór kolejnych danych
	bool isReadyRead = false;

	//Konstruktor, z słowem kluczowym explicit, z uwagi na jednoargumentowość
    explicit TcpConnection(QObject *parent = nullptr);

	//Destruktor
    ~TcpConnection();

	//Konfiguracja gniazda, głównie połączeń
    virtual void setSocket(QTcpSocket * socket);

	//Zawiera ostatnio odebrane dane. Wymagane celem docelowej transmisji do mainwindow
    QByteArray lastData;



protected:

	//Wskaźnik na gniazdo, na którym operuje ta klasa
    QTcpSocket * _mSocket = nullptr;

	//Zwrócenie wskaźnika
    QTcpSocket * _getSocket();

public slots:

	//Slot aktywowany w momencie pomyślnego połączenia z klientem
    virtual void connected();

	//Slot aktywowany w momencie odłączenia klienta
    virtual void disconnected();

	//Slot aktywowany w momencie przybycia nowych danych
    virtual void bytesWritten(qint64 bytes);

	//Slot aktywowany w momencie zmiany statusu gniazda (np przez erwanie połączenia)
    virtual void statesChanged(QAbstractSocket::SocketState socketState);

	//Slot aktywowany w momencie wystąpienia błędu na gnieździe)
    virtual void error(QAbstractSocket::SocketError sockError);

	//Slot aktywowany celem wysłąnia informacji o przybyciu nowych danych
	virtual void readyRead();

	//Slot aktywowany w momencie chęci wysłania danych (aktywowany z mainwindow za pomocą sygnału)
	void wrtieData(QByteArray src);

signals:

	//Emitowane, w momencie przybybia nowych danych
    void avaiableData();


};

#endif // TCPCONNECTION_H
