/********************************************************************************
** Form generated from reading UI file 'report.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORT_H
#define UI_REPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Report
{
public:
    QGridLayout *gridLayout;
    QCalendarWidget *Calendar1;
    QFormLayout *formLayout;
    QComboBox *comboBox;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *Button1;
    QLabel *pathOfSave;

    void setupUi(QWidget *Report)
    {
        if (Report->objectName().isEmpty())
            Report->setObjectName(QString::fromUtf8("Report"));
        Report->resize(774, 764);
        gridLayout = new QGridLayout(Report);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Calendar1 = new QCalendarWidget(Report);
        Calendar1->setObjectName(QString::fromUtf8("Calendar1"));
        Calendar1->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(Calendar1, 0, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetNoConstraint);
        comboBox = new QComboBox(Report);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(300, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, comboBox);

        doubleSpinBox = new QDoubleSpinBox(Report);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, doubleSpinBox);


        gridLayout->addLayout(formLayout, 3, 0, 1, 1);

        Button1 = new QPushButton(Report);
        Button1->setObjectName(QString::fromUtf8("Button1"));

        gridLayout->addWidget(Button1, 1, 0, 1, 1);

        pathOfSave = new QLabel(Report);
        pathOfSave->setObjectName(QString::fromUtf8("pathOfSave"));
        pathOfSave->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pathOfSave, 2, 0, 1, 1);

        QWidget::setTabOrder(Button1, Calendar1);

        retranslateUi(Report);

        QMetaObject::connectSlotsByName(Report);
    } // setupUi

    void retranslateUi(QWidget *Report)
    {
        Report->setWindowTitle(QApplication::translate("Report", "Form", nullptr));
        Button1->setText(QApplication::translate("Report", "Generuj Raport z Wybranego Dnia", nullptr));
        pathOfSave->setText(QApplication::translate("Report", "Miejsce Generowania Raportu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Report: public Ui_Report {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORT_H
