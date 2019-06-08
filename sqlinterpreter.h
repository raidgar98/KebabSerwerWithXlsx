#pragma once

#include <fstream>
#include <string>
#include <QTextEdit>
#include <QMessageBox>
#include <QMap>
#include <QMainWindow>

#include <QDebug>

#define cout qDebug()

//class MainWindow : public QMainWindow {};

class SQLInterpreter final : public QObject
{
	Q_OBJECT

private:

	//Path to src file
	QString			__mInputPath		{""};

	//Template String
	QString			__mSrc				{""};

	//Map of template of template argument as key associated with data to insert
	QMap<QString, QString> __mSymbols;

	//Methode to process all file, and send output by the only signal in this class
	void __mCompileFunction(const char separator, std::list<QString>& paramList, QString& query, const std::string & buff) const noexcept;

public:

	//In main constructor everythink is done
	SQLInterpreter() = delete;

	//No copy no move, just work
	SQLInterpreter(const SQLInterpreter&) = delete;
	SQLInterpreter(SQLInterpreter&&) = delete;

	//Standard destructor
	~SQLInterpreter();

	//My own delete operator. Have to make sure that destructor is called
	void operator delete(void *);

	//Main constructor. First is path to file, second is template and thrid is QObject inherance request
	SQLInterpreter(const QString& , QString , QObject * = nullptr) noexcept;

	//Process all and save it into __mInputPath file. Core Function
	bool save();

	//Resturns example, using first row as input data
	QString __mExampleFunction();

	//Returns amount of columns detected in file
	size_t __mAmountOfColumnsFunction() const;

	//Returns value from inserted key (it's just operator from map)
	QString operator[](const QString) const;

signals:

	//Sends to processed data as auerries
	void saveSQL(const QString& src);

public:

	//is everythnk setted nice. Ie if file can't be openede it's false
	bool isOk = false;
};
