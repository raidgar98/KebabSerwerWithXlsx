#ifndef REPORT_H
#define REPORT_H

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

namespace Ui {
class Report;
}

class Report : public QDialog
{
	Q_OBJECT
public:

	QSqlDatabase* db ;

	QMap<QString, double> myValues;

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

private:
	Ui::Report *ui;
};

#endif // REPORT_H


