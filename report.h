#pragma once

#include <QDialog>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxworksheet.h"
#include "xlsxcellformula.h"

#include <list>
#include <map>

namespace Ui {
class Report;
}

//Class responsible for report UI and is engine for xlsx report generating
class Report : public QDialog
{
	Q_OBJECT

public:

	//Class responsible for holding information about types of avaiable extras and dishes
	class DBresult
	{
	public:

		//varriables with exact same name as from database
		QString name, fullName;
		double val;
		bool isExtra = 0;
		//QDoubleSpinBox * dblSpin;

		//Constructor
		DBresult(const QString src1, const QString src2, const double val1, const bool Extra)
			:name{src1}, fullName{src2}, val{val1}, isExtra{Extra}
		{
			/*
			dblSpin = new QDoubleSpinBox();
			dblSpin->setValue(val);
			dblSpin->setSuffix(" PLN");
			dblSpin->setRange(0, std::numeric_limits<double>::max()-4);
			*/
		}

		DBresult(const DBresult& src) : name{src.name}, fullName{src.fullName}, val{src.val}, isExtra{src.isExtra} { }
		DBresult(DBresult&& src) : name{src.name}, fullName{src.fullName}, val{src.val}, isExtra{src.isExtra} { }

	};

	//Pointer on database connection, catched from mainwindow
	QSqlDatabase* db ;

	//Holds handy information about values. In future can be optimalized by changing into __mForms, and deleting this one
	std::map<QString, double> myValues;

	//Holds all prices
	std::list<DBresult> __mForms;

	//Auto-generated constructor, with one extra parameter (database)
	explicit Report(QSqlDatabase* ptr, QDialog *parent = nullptr);

	//Auto-generated destructor
	~Report();

	//Based on name finds price by SQL
	double getValueOn(const QString src) noexcept;

	//Load all avaiable dishes with prices to __mForms and to myValues
	void onLoad() noexcept;

	//This method has to be customize, how you want to generate xlsx
	void doStuff();

	//Translate name to fullName using __mForms
	QString translateName(const QString src) const noexcept;

	//Translate number into souce name
	QString translateSouce(const quint8 src) const noexcept;

	//Same as getValueOn
	double translateValue(const QString src) noexcept;

private slots:

	//Activated if user click 'generuj'
	void on_Button1_clicked();

//	virtual void on_SpinBox_value_Changed(double d);

	//Activated if user change smthing in comboBox
	void on_comboBox_currentIndexChanged(const QString &arg1);

	//Activated if somebody change value, use sql
	void on_doubleSpinBox_valueChanged(double arg1);

private:

	Ui::Report *ui;
};
