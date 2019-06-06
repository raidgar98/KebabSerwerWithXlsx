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

//Class responsible for UI and dcision making
class MainWindow : public QMainWindow
{
    Q_OBJECT

	//Responsible for orginizing connections and data transferring
	TCPSerwer *__mSerwerPointer = new TCPSerwer();

	//Data Base Connection
	QSqlDatabase __mDataBase;

	//Engine for CSV -> SQL conversion
	SQLInterpreter* __mCSV2SQLengine = nullptr;

	//For storaging fast coming data
	QQueue<QString> __mDataBuffor;

	bool __mIsDataBaseReady = false;

	//Storing actual serwer status (for UI)
	bool __mCurrentSerwerState = false;

	//Log types
	enum LogType
	{
		Send,
		Received,
		SQLSend,
		SQLReceived,
		Info
	};


	//For syncing buffor with SQL during update
	void __mSyncFunction() noexcept;

public:

	//Here we store answer from last active socket
	QPair<QTcpSocket* , QByteArray> mAnswer;

	//Auto-Generated Constructor
	explicit MainWindow(QWidget *parent = nullptr);

	//Auto-Generated Destructor
    ~MainWindow();

	//This Methode is responible for switching enable in addition to diffrent serwer state
	void mChangeStateFunction(bool changeTo);

	//Decision making methode
	bool mMakeDecissionFunction(QByteArray& src, const quint8);

	//Methode for logging, only this methode has access to TextField in UI
	void mLogFunction(QString src, LogType t);

private slots:

	//Slot activated if 'start' button clicked
    void on_Button1_clicked();

	//Slot activated if 'stop' button clicked
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
