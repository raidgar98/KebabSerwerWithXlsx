#include <QMessageBox>
#include "report.h"
#include "ui_report.h"
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <QDebug>
#include <QFormLayout>

#define cout qDebug()

Report::Report(QSqlDatabase* ptr,  QDialog *parent) :
	QDialog(parent), db{ptr},
	ui(new Ui::Report)
{
	ui->setupUi(this);
	onLoad();
}

Report::~Report()
{
	delete ui;
}

double Report::getValueOn(const QString src) noexcept
{
/*
 //Old way
 *
	QString orginal = "SELECT val FROM prices WHERE name='::0';";
	QString temp = orginal;
	db->open();
	QSqlQuery q1(temp.replace("::0", src));
	q1.exec();
	db->close();
	q1.next();
	return (q1.value(0).toDouble());

*/
	for(auto var : __mForms)
		if(var.name == src) return var.val;
}

void Report::onLoad() noexcept
{

	db->open();
	QSqlQuery q1("SELECT COUNT(*) FROM prices;");
	q1.exec();
	db->close();
	q1.next();
	const quint16 countPrices = static_cast<quint16>(q1.value(0).toInt());
	quint16 counter = 1;

	while (counter != countPrices)
	{
		QString preQuerry = "SELECT * FROM prices WHERE idPrice=::1;";
		preQuerry.replace("::1", QString::number(counter));
		counter++;

		db->open();
		QSqlQuery q(preQuerry);
		q.exec();
		db->close();

		const quint8 namePos = static_cast<quint8>(q.record().indexOf("name"));
		const quint8 valPos = static_cast<quint8>(q.record().indexOf("val"));
		const quint8 fullNamePos = static_cast<quint8>(q.record().indexOf("fullName"));
		const quint8 isExtraPos = static_cast<quint8>(q.record().indexOf("isExtra"));

		q.next();

		__mForms.push_back(

					DBresult(
							   q.value(namePos).toString(), q.value(fullNamePos).toString(),
							   q.value(valPos).toDouble(), q.value(isExtraPos).toBool())

						   );

		ui->comboBox->addItem(__mForms.back().fullName);
		myValues[__mForms.back().name] = __mForms.back().val;

		/*
		cout << "Elo1";

		ui->form1->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
		cout << "Elo2";
		ui->form2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
		cout << "Elo3";

		if(switcher)
		{
			ui->form1->insertRow(0, __mForms.back().fullName, __mForms.back().dblSpin);
			cout << "Elo4";
		}
		else
		{
			cout<<"Bum";
			ui->form2->insertRow(0, __mForms.back().fullName, __mForms.back().dblSpin);
			cout << "Elo5";
		}

		//QObject::connect(__mForms.back().dblSpin, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &Report::on_SpinBox_value_Changed);

		switcher = !switcher;*/
	}


	/*
	ui->DuzCia->setValue(getValueOn("DuzCia"));
	myValues["DuzCia"] = ui->DuzCia->value();
	ui->MalCia->setValue(getValueOn("MalCia"));
	myValues["MalCia"] = ui->MalCia->value();
	ui->DuzBul->setValue(getValueOn("DuzBul"));
	myValues["DuzBul"] = ui->DuzBul->value();
	ui->MalBul->setValue(getValueOn("MalBul"));
	myValues["MalBul"] = ui->MalBul->value();
	ui->DuzPit->setValue(getValueOn("DuzPit"));
	myValues["DuzPit"] = ui->DuzPit->value();
	ui->MalPit->setValue(getValueOn("MalPit"));
	myValues["MalPit"] = ui->MalPit->value();
	ui->DuzKub->setValue(getValueOn("DuzKub"));
	myValues["DuzKub"] = ui->DuzKub->value();
	ui->MalKub->setValue(getValueOn("MalKub"));
	myValues["MalKub"] = ui->MalKub->value();
	ui->DuzVegGrek->setValue(getValueOn("DuzVegGrek"));
	myValues["DuzVegGrek"] = ui->DuzVegGrek->value();
	ui->MalVegGrek->setValue(getValueOn("MalVegGrek"));
	myValues["MalVegGrek"] = ui->MalVegGrek->value();
	ui->VegKebCiast->setValue(getValueOn("VegKebCiast"));
	myValues["VegKebCiast"] = ui->VegKebCiast->value();
	ui->VegKebBul->setValue(getValueOn("VegKebBul"));
	myValues["VegKebBul"] = ui->VegKebBul->value();
	ui->BBQCia->setValue(getValueOn("BBQCia"));
	myValues["BBQCia"] = ui->BBQCia->value();
	ui->BBQBul->setValue(getValueOn("BBQBul"));
	myValues["BBQBul"] = ui->BBQBul->value();
	ui->DuzFryt->setValue(getValueOn("DuzFryt"));
	myValues["DuzFryt"] = ui->DuzFryt->value();
	ui->MalFryt->setValue(getValueOn("MalFryt"));
	myValues["MalFryt"] = ui->MalFryt->value();
	ui->ZapWiej->setValue(getValueOn("ZapWiej"));
	myValues["ZapWiej"] = ui->ZapWiej->value();
	ui->ZapDiab->setValue(getValueOn("ZapDiab"));
	myValues["ZapDiab"] = ui->ZapDiab->value();
	ui->ZapVeg->setValue(getValueOn("ZapVeg"));
	myValues["ZapVeg"] = ui->ZapVeg->value();
	ui->ZapSzpin->setValue(getValueOn("ZapSzpin"));
	myValues["ZapSzpin"] = ui->ZapSzpin->value();
	ui->ZapCust->setValue(getValueOn("ZapCust"));
	myValues["ZapCust"] = ui->ZapCust->value();
	ui->TempDish->setValue(getValueOn("TempDish"));
	myValues["TempDish"] = ui->TempDish->value();
	ui->FirstSouce->setValue(getValueOn("FirstSouce"));
	myValues["FirstSouce"] = ui->FirstSouce->value();
	ui->SecondSouce->setValue(getValueOn("SecondValue"));
	myValues["SecondValue"] = ui->SecondSouce->value();
	ui->Meat->setValue(getValueOn("Meat"));
	myValues["Meat"] = ui->Meat->value();
	ui->Salad->setValue(getValueOn("Salad"));
	myValues["Salad"] = ui->Salad->value();
	ui->Fries->setValue(getValueOn("Fries"));
	myValues["Fries"] = ui->Fries->value();
	ui->Cheese->setValue(getValueOn("Cheese"));
	myValues["Cheese"] = ui->Cheese->value();
	ui->Extras->setValue(getValueOn("Extras"));
	myValues["Extras"] = ui->Extras->value();
	ui->TakeAway->setValue(getValueOn("TakeAway"));
	myValues["TakeAway"] = ui->TakeAway->value();
	*/
}

void Report::doStuff()
{
	//First make micromapping of data arrived from database
	db->open();

	QSqlQuery q("SELECT * FROM orders WHERE orderID=1;");
	q.exec();

	db->close();

	const quint8 orderID = static_cast<quint8>(q.record().indexOf("orderID"));
	const quint8 dishName = static_cast<quint8>(q.record().indexOf("dishName"));
	const quint8 dishSouce = static_cast<quint8>(q.record().indexOf("dishSouce"));
	const quint8 extraMeat = static_cast<quint8>(q.record().indexOf("extraMeat"));
	const quint8 extraSalad = static_cast<quint8>(q.record().indexOf("extraSalad"));
	const quint8 extraFries = static_cast<quint8>(q.record().indexOf("extraFries"));
	const quint8 extraCheese = static_cast<quint8>(q.record().indexOf("extraCheese"));
	const quint8 otherExtras = static_cast<quint8>(q.record().indexOf("otherExtras"));
	const quint8 takeAway = static_cast<quint8>(q.record().indexOf("takeAway"));
	const quint8 orderDateTime = static_cast<quint8>(q.record().indexOf("orderDateTime"));

	//Because of getting many values at once not working, so i get minimum and maximum id and next i get them one by one, simply incrementing
	QString getIDtemplate = "SELECT ::0(orderID) FROM orders WHERE orderDateTime LIKE '::1 %';";
	QString getCount = "SELECT COUNT(*) FROM orders WHERE orderDateTime LIKE '::1 %';";
	getIDtemplate.replace("::1", ui->Calendar1->selectedDate().toString("yyyy-MM-dd"));
	getCount.replace("::1", ui->Calendar1->selectedDate().toString("yyyy-MM-dd"));
	QString getIdMin = getIDtemplate;
	QString getIdMax = getIDtemplate;
	getIdMin.replace("::0", "MIN");
	getIdMax.replace("::0", "MAX");

	size_t minID = 0, maxID = 0;

	db->open();

	QSqlQuery q1(getIdMin);
	QSqlQuery q2(getIdMax);
	QSqlQuery q3(getCount);

	q1.exec();
	q2.exec();
	q3.exec();

	//cout << q1.lastQuery();
	//cout << q2.lastQuery();

	db->close();
	q1.next();
	minID = static_cast<size_t>(q1.value(0).toInt());
	q2.next();
	maxID = static_cast<size_t>(q2.value(0).toInt());

	q1.clear();
	q2.clear();

	//Beginning of raport generation
	QXlsx::Document xlsx;
	xlsx.addSheet("Raport");

	//Setting formats
	QXlsx::Format format;
	QXlsx::Format formatCALK;
	QXlsx::Format formatSTR;
	QXlsx::Format formatDATE;
	QXlsx::Format formatFINAL;

	format.setNumberFormat("#00.00");
	format.setHorizontalAlignment(QXlsx::Format::HorizontalAlignment::AlignHCenter);
	formatSTR.setNumberFormat("@");
	formatDATE.setNumberFormat("YYYY-MM-DD HH:MM:SS");
	formatDATE.setHorizontalAlignment(QXlsx::Format::HorizontalAlignment::AlignHCenter);
	formatCALK.setNumberFormat("#0");
	formatCALK.setHorizontalAlignment(QXlsx::Format::HorizontalAlignment::AlignHCenter);
	formatFINAL.setFontColor(QColor(240, 0, 0));
	formatFINAL.setNumberFormat("#00.00");
	formatFINAL.setHorizontalAlignment(QXlsx::Format::HorizontalAlignment::AlignHCenter);

	//Writing headers of columns
	xlsx.write(1,1,"ID zamówienia");
	xlsx.write(1,2, "Nazwa Dania");
	xlsx.write(1,3, "Rodzaj sosu");
	xlsx.write(1,4, "Dodatkowe Mięso");
	xlsx.write(1,5, "Dodatkowa Sałatka");
	xlsx.write(1,6, "Dodatkowe Frytki");
	xlsx.write(1,7, "Dodatkowy Ser");
	xlsx.write(1,8, "Inne Dodatki");
	xlsx.write(1,9, "Na wynos");
	xlsx.write(1,10, "Koszt Dania");
	xlsx.write(1,11,"Czas wykonania zamówienia");

	q3.next();
	int lastRecord = q3.value(0).toInt() + 1;

	//Setting summary
	xlsx.write((lastRecord)+1, 1, "Ilość pozycji",formatSTR);
	xlsx.write((lastRecord)+2, 1, QString::number(maxID-minID+1).toInt(), formatCALK);

	xlsx.write((lastRecord)+1,2, "Cena: ",formatSTR);
	xlsx.write((lastRecord)+2,2, "Wartość: ",formatSTR);

	xlsx.write((lastRecord)+1, 3, myValues["SecondValue"], format);
	xlsx.write((lastRecord)+2, 3, "=LICZ.JEŻELI(C2:C"+QString::number(lastRecord)+"; \"Mieszany\")*C"+QString::number(lastRecord+1));

	xlsx.write((lastRecord)+1, 4, myValues["Meat"],format);
	xlsx.write((lastRecord)+2, 4, "=SUMA(D2:D"+QString::number(lastRecord)+")*D"+QString::number(lastRecord+1), format);

	xlsx.write((lastRecord)+1, 5, myValues["Salad"],format);
	xlsx.write((lastRecord)+2, 5, "=SUMA(E2:E"+QString::number(lastRecord)+")*E"+QString::number(lastRecord+1), format);

	xlsx.write((lastRecord)+1, 6, myValues["Fries"],format);
	xlsx.write((lastRecord)+2, 6, "=SUMA(F2:F"+QString::number(lastRecord)+")*F"+QString::number(lastRecord+1), format);

	xlsx.write((lastRecord)+1, 7, myValues["Cheese"],format);
	xlsx.write((lastRecord)+2, 7,"=SUMA(G2:G"+QString::number(lastRecord)+")*G"+QString::number(lastRecord+1),format);

	xlsx.write((lastRecord)+1, 8, myValues["Extras"],format);
	xlsx.write((lastRecord)+2, 8, "=SUMA(H2:H"+QString::number(lastRecord)+")*H"+QString::number(lastRecord+1), format);

	xlsx.write((lastRecord)+1, 9, myValues["TakeAway"],format);
	xlsx.write((lastRecord)+2, 9, "=SUMA(I2:I"+QString::number(lastRecord)+")*I"+QString::number(lastRecord+1), format);

	xlsx.write((lastRecord)+1, 10, "PODSUMOWANIE",formatSTR);
	xlsx.write((lastRecord)+2, 10, "=SUMA(J2:J"+QString::number(lastRecord)+") + SUMA(C"+QString::number(lastRecord+2)+":I"+QString::number(lastRecord+2)+")", formatFINAL);

	//Template for querry for selecting record one by one
	const QString selectTemplate = "SELECT * FROM orders WHERE orderID=::0 AND orderDateTime LIKE '::1 %';";
	int licznik = minID;
	int row = 2;
	while(licznik <= maxID)
	{
		QString actQuerry =selectTemplate;
		actQuerry.replace("::0", QString::number(licznik));
		actQuerry.replace("::1", ui->Calendar1->selectedDate().toString("yyyy-MM-dd"));
		licznik++;
		db->open();
		QSqlQuery actq(actQuerry);
		actq.exec();
		db->close();
		actq.next();

		//If empty just continue
		if(actq.isNull(0)) continue;

		//Filling columns and rows
		xlsx.write(row,1,actq.value(orderID).toInt(),formatCALK);
		xlsx.write(row,2, translateName(actq.value(dishName).toString()), formatSTR);
		xlsx.write(row,3, translateSouce(static_cast<quint8>(actq.value(dishSouce).toInt())),formatSTR);
		xlsx.write(row,4, actq.value(extraMeat).toInt(), formatCALK);
		xlsx.write(row,5, actq.value(extraSalad).toInt(), formatCALK);
		xlsx.write(row,6, actq.value(extraFries).toInt(), formatCALK);
		xlsx.write(row,7, actq.value(extraCheese).toInt(), formatCALK);
		xlsx.write(row,8, actq.value(otherExtras).toInt(), formatCALK);
		xlsx.write(row,9, actq.value(takeAway).toInt(), formatCALK);
		xlsx.write(row,10, translateValue(actq.value(dishName).toString()), format);
		xlsx.write(row,11, actq.value(orderDateTime).toDateTime().toString("yyyy-MM-dd hh:mm:ss"), formatDATE);

		row++;

		actq.clear();
	}

	//Saving and displaying info about success
	xlsx.saveAs(ui->pathOfSave->text());
	ui->Button1->setEnabled(true);
	QMessageBox a(QMessageBox::Icon::Information, "Zakończono", "Dokumnent: \n"+ ui->pathOfSave->text() + "\n został wygenerowany.");
	a.show();
	a.exec();
}

QString Report::translateName(const QString src) const noexcept
{

	for(auto var : __mForms)
		if(var.name == src) return var.fullName;

	/*
	QString orginal = "SELECT fullName FROM prices WHERE name='::0';";
	QString temp = orginal;
	db->open();
	QSqlQuery q1(temp.replace("::0", src));
	q1.exec();
	db->close();
	q1.next();
	return (q1.value(0).toString());
	*/

	/*

		if( src == "DuzCia") return "Duże Ciasto";
		if( src == "MalCia") return "Małe Ciasto";
		if( src == "DuzBul") return "Duża Bułka";
		if( src == "MalBul") return "Mała Bułka";
		if( src == "DuzPit") return "Duża Pita";
		if( src == "MalPit") return "Mała Pita";
		if( src == "MalKub") return "Mału Kubełek";
		if( src == "DuzKub") return "Duży Kubełek";
		if( src == "MalGrek") return "Mały Vegański po Grecku";
		if( src == "DuzGrek") return "Duży Vegański po Grecku";
		if( src == "VegCia") return "Vegański Kebab w Cieście";
		if( src == "VegBul") return "Vegański Kebab w Bułce";
		if( src == "BBQCia") return "Warzywa na Grillu w Cieście";
		if( src == "BBQBul") return "Warzywa na Grillu w Bułce";
		if( src == "DuzFry") return "Duże Frytki";
		if( src == "MalFry") return "Małe Frytki";
		if( src == "ZapWie") return "Zapiekanka Wiejska";
		if( src == "ZapDia") return "Zapiekanka Diabelska";
		if( src == "ZapVeg") return "Zapiekanka Vegańska";
		if( src == "ZapSzp") return "Zapiekanka Szpinakowa";
		if( src == "ZapDos") return "Zapiekanka Dowolna";
		if( src == "FirstSouce") return "Pierwszy Sos";
		if( src == "SecondValue") return "Drugi Sos";
		if( src == "Meat") return "Dodatkowe Mięso";
		if( src == "Salad") return "Dodatkowa Sałatka";
		if( src == "Fries") return "Dodatkowe Frytki";
		if( src == "Cheese") return "Dodatkowy Ser";
		if( src == "Extras") return "Inne Dodatki";
		if( src == "TakeAway") return "Na Wynos";
		if( src == "Temp") return "Potrawa Tymczasowa";
		//TO DO: Standarize names

		*/

}

double Report::translateValue(const QString src) noexcept
{
/*	if( src == "DuzCia") return ui->DuzCia->value();
	if( src == "MalCia") return ui->MalCia->value();
	if( src == "DuzBul") return ui->DuzBul->value();
	if( src == "MalBul") return ui->MalBul->value();
	if( src == "DuzPit") return ui->DuzPit->value();
	if( src == "MalPit") return ui->MalPit->value();
	if( src == "MalKub") return ui->DuzKub->value();
	if( src == "DuzKub") return ui->MalKub->value();
	if( src == "MalGrek") return ui->MalVegGrek->value();
	if( src == "DuzGrek") return ui->DuzVegGrek->value();
	if( src == "VegCia") return ui->VegKebCiast->value();
	if( src == "VegBul") return ui->VegKebBul->value();
	if( src == "BBQCia") return ui->BBQCia->value();
	if( src == "BBQBul") return ui->BBQBul->value();
	if( src == "DuzFry") return ui->DuzFryt->value();
	if( src == "MalFry") return ui->MalFryt->value();
	if( src == "ZapWie") return ui->ZapWiej->value();
	if( src == "ZapDia") return ui->ZapDiab->value();
	if( src == "ZapVeg") return ui->ZapVeg->value();
	if( src == "ZapSzp") return ui->ZapSzpin->value();
	if( src == "ZapDos") return ui->ZapCust->value();
	if( src == "Temp") return ui->TempDish->value();
	*/
/*	for(auto var : __mForms)
	{
		if(var.name == src) return var.val;
	}

*/

	return getValueOn(src);
}

QString Report::translateSouce(const quint8 src) const noexcept
{
	switch(src)
	{
		case 0: return "Brak Sosu";
		case 1: return "Mieszany";
		case 2: return "Łagodny";
		case 3: return "Ostry";
	}
}

void Report::on_Button1_clicked()
{
	QString path = QFileDialog::getExistingDirectory(this);
	if(path == QString()) return;
	ui->Button1->setEnabled(false);
	QDate date = ui->Calendar1->selectedDate();
	path +="/"+date.toString("yyyy-MM-dd-dddd")+"_report.xlsx";
	ui->pathOfSave->setText(path);
	QMessageBox a(QMessageBox::Icon::Warning, "Uwaga!", "Aplikacja może przez chwilę nie odpowiadać, ponieważ generowanie raportu jest obciążające dla komputera");
	a.show();
	a.exec();
	doStuff();
}

/*
void Report::on_SpinBox_value_Changed(double d)
{
	QDoubleSpinBox * temp = static_cast<QDoubleSpinBox*>(sender());
	DBresult * res = nullptr;

	for(auto it = __mForms.begin(); it != __mForms.end(); it++)
	{
		if((it->dblSpin) == temp)
		{
			res = &(*it);
			break;
		}
	}

	QString quer = "UPDATE prices SET val=::1 WHERE name='::2';";
	quer.replace("::1", QString::number(d));
	quer.replace("::2", res->name);
	db->open();
	QSqlQuery q(quer);
	q.exec();
	db->close();

	res->val = d;
}
*/

void Report::on_comboBox_currentIndexChanged(const QString &arg1)
{
	for(auto var : __mForms)
	{
		if(var.fullName == arg1)
		{
			ui->doubleSpinBox->setValue(var.val);
			ui->comboBox->setToolTip(var.name);
			return;
		}
	}
}

void Report::on_doubleSpinBox_valueChanged(double arg1)
{
	QString quer = "UPDATE prices SET val=::1 WHERE name='::2';";
	quer.replace("::1", QString::number(arg1));
	//In tooltip name is stored, so it's easier to look in database
	quer.replace("::2", ui->comboBox->toolTip());
	db->open();
	QSqlQuery q(quer);
	q.exec();
	db->close();

	for(auto var : __mForms)
	{
		if(var.name == ui->comboBox->toolTip())
		{
			var.val = arg1;
			return;
		}
	}
}
