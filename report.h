#pragma once

#include <QDialog>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QMap>
#include <QThread>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxworksheet.h"
#include "xlsxcellformula.h"
#include <QDoubleSpinBox>

#include <list>

namespace Ui {
class Report;
}

class Report : public QDialog
{
	Q_OBJECT

public:


	class DBresult
	{
	public:

		QString name, fullName;
		double val;
		bool isExtra = 0;
		//QDoubleSpinBox * dblSpin;


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

	QSqlDatabase* db ;

	QMap<QString, double> myValues;

	std::list<DBresult> __mForms;

	explicit Report(QSqlDatabase* ptr, QDialog *parent = nullptr);
	~Report();

	double getValueOn(const QString src) noexcept;

	void onLoad() noexcept;

	QThread myThread;

	QString dbName, dbPath;

	void doStuff();

	QString translateName(const QString src) const noexcept;

	QString translateSouce(const quint8 src) const noexcept;

	double translateValue(const QString src) const noexcept;

private slots:

	void on_Button1_clicked();

//	virtual void on_SpinBox_value_Changed(double d);

	void on_comboBox_currentIndexChanged(const QString &arg1);

	void on_doubleSpinBox_valueChanged(double arg1);

private:

	Ui::Report *ui;
};
