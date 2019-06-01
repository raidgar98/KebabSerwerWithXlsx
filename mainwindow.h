#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpserwer.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlRecord>
#include <QQueue>
#include "sqlinterpreter.h"


namespace Ui {
class MainWindow;
}

//Klasa odpowiedzialna za szatę graficzną, oraz decyzyjność
class MainWindow : public QMainWindow
{
    Q_OBJECT

	//Klasa zarządzająca wszystkimi operacjami związanymi z połączeniami sieciowymi
    TCPSerwer *serw = new TCPSerwer();

	//Konfiguracja Bazy Danych
	QSqlDatabase db;

	//Silnik konwersji CSV na SQL
	SQLInterpreter* engine = nullptr;

	//For storaging fast coming data
	QQueue<QString> buffor;

	//Inofrmacja czy baza danych jest gotowa do użytku
	bool isDBReady = false;

	//Zmienna przechowująca, aktualny stan serwera, używana do obsługi interfejsu
    bool currState = false;

	//Rodzaje logów
	enum LogType
	{
		Send,
		Received,
		SQLSend,
		SQLReceived,
		Info
	};


	//For syncing buffor with SQL during update
	void sync() noexcept;

public:

	//W tym miejscu zostaje zapisana najnowsza wiadomość od klienta oraz z jakiego gniazda on nadeszła
	QPair<QTcpSocket* , QByteArray> mAnswer;

	//Konstruktor, z uwagi na jednoargumentowość z słówkiem kluczowym explicit, aby nie został użyty do 'dzikiej' konwersji
	explicit MainWindow(QWidget *parent = nullptr);

	//Destruktor
    ~MainWindow();

	//Metoda odpowiedzialna za aktywowanie, oraz deaktywowanie odpowiednich przycisków w zależności od aktualnego stanu serwera
    void changeState(bool changeTo);

	//Metoda decyzyjna, zawiera instrukcje do wykonania, w przypadku pojawienia się konkretnych sygnałów
	bool doStuff(QByteArray& src, const quint8);

	//Metoda służąca do logowania różnych informacji. Jako jedyna ma dostęp do pola tekstowego
	void log(QString src, LogType t);

private slots:

	//Metoda aktywowana, w momencie naciśnięcia przycisku 'start'
    void on_Button1_clicked();

	//Metoda aktywowana, w momencie naciśnięcia przycisku 'stop'
    void on_Button2_clicked();

	//Metoda odpowiedzialne za wyświetlenie najnowszej wiadomości od klienta, oraz ustawienie niezbędnych połączeń, celem ułatwienia wysłania odpowiedzi.
	//Znajduje się w niej również wywołanie metody decyzyjnej
    void disp();

	//Metoda służąca do włączania automatycznego przewijania loggów
	void on_checkBox_stateChanged(int arg1);

	void on_Button3_clicked();

public slots:

	//Writes SQL to local, our saviour, database
	void writeLocalSQL(const QString& src) noexcept;

private:

	//Wskaźnik na interfejs
    Ui::MainWindow *ui;

signals:

	//Sygnał emitowany, w momencie chęci wysłania odpowiedzi. Połączenie występuje w metodzie disp
	void writeAvaiable(QByteArray data);


};

#endif // MAINWINDOW_H
