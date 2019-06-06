#include "report.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QStandardPaths>
#include <QMessageBox>

#define cout qDebug()
/*

  INSERT INTO orders(dishName, dishSouce, extraMeat, extraSalad, extraFries, extraCheese,
	otherExtras, takeAway, isComplete, orderDateTime)
		VALUES("elo", 1, 1, 1, 1, 1, 1, 1, 1, CURRENT_TIMESTAMP);

*/
void MainWindow::mWriteLocalSQLFunction(const QString & src) noexcept
{
        cout<<"Sending SQL: "<<src;
	if(!__mIsDataBaseReady) return;
	__mDataBase.open();
	QSqlQuery q(src);

	q.exec();

	__mDataBase.close();
	//q.clear();
	//q.finish();
}

void MainWindow::__mSyncFunction() noexcept
{
	while(__mDataBuffor.size() != 0)
	{
		QString data = __mDataBuffor.first();
		__mDataBuffor.pop_front();

		QString q = "INSERT INTO orders(dishName, dishSouce, extraMeat, extraSalad, extraFries, extraCheese,"
					" otherExtras, takeAway, isComplete, orderDateTime) VALUES( ";

		bool isComa = false;

		for(int i = data.indexOf("VALUE") ; i < data.length(); i++)
		{
			if(!isComa)
			{
				if(data[i] == ',')
				{
					isComa = true;
					continue;
				}else continue;
			}
			if(data[i] != '\r' && data[i] != '\n' ) q+=data[i]; else break;
		}

		//cout<<"Sending QUERRY: "<<q;
		mWriteLocalSQLFunction(q);
		mLogFunction(q, LogType::SQLSend);
	}
	QMessageBox a(QMessageBox::Icon::NoIcon, "Gotowe", "Pomyślnie zaimportowano wszystkie dane");
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	cout<<"Step 1";
	connect(__mSerwerPointer, &TCPSerwer::avaiableRead, this, &MainWindow::mAnswerNewDataFunction);

	__mDataBase = QSqlDatabase::addDatabase("QSQLITE");
	__mDataBase.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/allOrders");

	if(__mDataBase.open())
	{
		__mIsDataBaseReady=true;
		cout << "Działa";
	}
	else
	{
		__mIsDataBaseReady=false;
		cout << "Nie działa";
	}
	__mDataBase.close();
	cout<<"Step 2";
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::mChangeStateFunction(bool changeTo)
{
	if(changeTo == __mCurrentSerwerState) return;

	if(changeTo)
	{
		if(__mSerwerPointer->listen(QHostAddress::Any, static_cast<quint16>(ui->portBox->value())))
		{
			ui->Button1->setEnabled(false);
			ui->Button2->setEnabled(true);
			ui->portBox->setEnabled(false);
			__mCurrentSerwerState = true;
			ui->Text1->append("<h4 style=\"color: 'green';\">"+QTime::currentTime().toString() + ">> Started</h4>\n");
		}
		else
		{
			QMessageBox a(QMessageBox::Icon::Critical, "Error", "Error occured, cannot start server");
			a.show();
			a.exec();
		}
	}
	else
	{
		__mSerwerPointer->close();
		__mCurrentSerwerState = false;
		ui->Button1->setEnabled(!false);
		ui->Button2->setEnabled(!true);
		ui->portBox->setEnabled(!false);
		ui->Text1->append("<h4 style=\"color: 'red';\">"+QTime::currentTime().toString() + ">> Stopped</h4>\n");
	}

}

void MainWindow::on_Button1_clicked()
{
	mChangeStateFunction(true);
}

void MainWindow::on_Button2_clicked()
{
	mChangeStateFunction(false);
	//sync();
}

void MainWindow::mAnswerNewDataFunction()
{
	//cout << this << " disp Działa";
	TcpConnection * tempSck = __mSerwerPointer->dataQueueRead.first().first;
	QByteArray temp = __mSerwerPointer->dataQueueRead.front().second;
	QObject::connect(this, &MainWindow::writeAvaiable, tempSck, &TcpConnection::wrtieData);
	__mSerwerPointer->dataQueueRead.pop_front();
	mLogFunction(temp, LogType::Received);
	//cout<<this << "zaloggowałem: " <<temp;
	if(mMakeDecissionFunction(temp, tempSck->id))
	{
		mLogFunction(temp, LogType::Send);
		//	cout << this << "disp: Wysyłam " <<temp;
		emit writeAvaiable(temp);
	}
	else
	{
		//	cout << this << "disp: Wysyłam " <<temp;
		if(temp == "\r\n")
		{
			return;
		}else
		{
			mLogFunction("Err\r\n", LogType::Send);
			emit writeAvaiable("Err\r\n");
		}
	}
}

bool MainWindow::mMakeDecissionFunction(QByteArray & src, const quint8 id)
{
	//cout << this << "Zaczynam robotę";
	QByteArray data = src;
	cout << "Data size: "<<data.size();
	//log(src, LogType::Received);
	if(data == "hello server \r\n\r\n\r\n")
	{
		src = "ok\r\n";
		//log(src, LogType::Send);
		return true;
	}else if (data.indexOf("^\r\n")!=-1)
	{
		src = "\r\n";
		mLogFunction("User "+ QString::number(id) + " Disconnected", LogType::Info);
		//sync();
		return false;

	}
	else if (data.indexOf("^&\r\n")!=-1)
	{
		src = "ok\r\n";
		mLogFunction("User "+ QString::number(id) + " Connected", LogType::Info);
		return true;
	}
	else
	{
		src = "ok\r\n";
		mLogFunction(src , LogType::Received);
		//if(data == "") return true;
		data.chop(2);
		QFile a("temp.txt");
		a.open(QFile::OpenModeFlag::WriteOnly);
		a.write(data);

		a.close();

		__mCSV2SQLengine = new SQLInterpreter("temp.txt", "INSERT INTO orders(dishName, dishSouce, extraMeat, extraSalad, extraFries, extraCheese, otherExtras, takeAway, isComplete, orderDateTime) VALUES('::1', ::2, ::3, ::4, ::5, ::6, ::7, ::8, ::9, '::x10');");
		QObject::connect(__mCSV2SQLengine, &SQLInterpreter::saveSQL, this, &MainWindow::mWriteLocalSQLFunction);

		__mCSV2SQLengine->save();

		//DEBUG!!!!!!!!!!!!

		//QFile::remove("temp.txt");

		return true;
	}
}

void MainWindow::mLogFunction(QString src, LogType t)
{
	//cout << this << "logguje: "<< src;
	QString temp = src;
	src = "";
	for(int i = 0; i < temp.length(); i++)
	{
		if(temp[i] == '\n' || temp[i] == '\r') break; else src+=temp[i];
	}

	if(t== LogType::Send)
	{
		ui->Text1->append("<h4 style=\"color: 'blue';\">"+QTime::currentTime().toString() + ">> Send: " + src + "</h4>\n");
	}
	else if (t == LogType::Received)
	{
		ui->Text1->append("<h4 style=\"color: 'orange';\">"+QTime::currentTime().toString() + ">> Received: " + src + "</h4>\n");
	}
	else if( t == LogType::SQLSend )
	{
		ui->Text1->append("<h4 style=\"color: 'violet';\">"+QTime::currentTime().toString() + ">> Send Query: " + src + "</h4>\n");
	}
	else if (t == LogType::SQLReceived)
	{
		ui->Text1->append("<h4 style=\"color: 'yellow';\">"+QTime::currentTime().toString() + ">> Received SQL Result: " + src + "</h4>\n");
	}
	else if (t == LogType::Info)
	{
		ui->Text1->append("<h4 style=\"color: 'white';\">"+QTime::currentTime().toString() + ">> Info: " + src + "</h4>\n");
	}

	if(ui->checkBox->isChecked()) ui->Text1->ensureCursorVisible();

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
	if(ui->checkBox->isChecked()) ui->Text1->ensureCursorVisible();
}

void MainWindow::on_Button3_clicked()
{
	/*cout << "Rozpoczynam usuwanie bazy";
	db.close();
	cout << "Zamknięto Połączenia";
	QString tempName= db.connectionName();
	QString pathToDb = db.databaseName();
	cout << "Zapamiętano nazwę bazy";*/

	Report dial(&__mDataBase);
	dial.setModal(true);
	dial.show();
	dial.topLevelWidget();
	dial.exec();

	cout << "Zamknięto Raport - okno. Wskrzeszanie połączenia";
/*
	//QSqlDatabase::removeDatabase(dial.db.connectionName());
	cout << "Ładowanie sterowinka";
	db = QSqlDatabase::database(tempName);
	cout << "Ładowanie connection Stringa";
	db.setDatabaseName(pathToDb);*/

}
