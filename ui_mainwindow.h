/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *portBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Button1;
    QPushButton *Button2;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QCheckBox *checkBox;
    QTextEdit *Text1;
    QPushButton *Button3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(957, 346);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        portBox = new QSpinBox(centralWidget);
        portBox->setObjectName(QString::fromUtf8("portBox"));
        portBox->setMinimum(1024);
        portBox->setMaximum(62000);
        portBox->setValue(12345);

        horizontalLayout->addWidget(portBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Button1 = new QPushButton(centralWidget);
        Button1->setObjectName(QString::fromUtf8("Button1"));

        horizontalLayout_2->addWidget(Button1);

        Button2 = new QPushButton(centralWidget);
        Button2->setObjectName(QString::fromUtf8("Button2"));
        Button2->setEnabled(false);

        horizontalLayout_2->addWidget(Button2);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 3, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(18);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_3->addWidget(label_8);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_3->addWidget(label_9);


        gridLayout->addLayout(verticalLayout_3, 0, 2, 2, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("background-color: \"orange\";"));

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(18);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_2->addWidget(label_10);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_2->addWidget(label_11);


        gridLayout->addLayout(verticalLayout_2, 0, 4, 2, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("background-color: \"yellow\";"));

        gridLayout->addWidget(label_7, 0, 5, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(18);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout_5->addWidget(label_14);

        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        verticalLayout_5->addWidget(label_15);


        gridLayout->addLayout(verticalLayout_5, 0, 6, 2, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("background-color: \"blue\";"));

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("background-color: \"violet\";"));

        gridLayout->addWidget(label_6, 1, 5, 1, 1);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setAutoFillBackground(false);
        checkBox->setIconSize(QSize(20, 20));
        checkBox->setChecked(true);
        checkBox->setTristate(false);

        gridLayout->addWidget(checkBox, 2, 1, 1, 3);

        Text1 = new QTextEdit(centralWidget);
        Text1->setObjectName(QString::fromUtf8("Text1"));
        Text1->setStyleSheet(QString::fromUtf8(""));
        Text1->setFrameShadow(QFrame::Raised);
        Text1->setReadOnly(true);

        gridLayout->addWidget(Text1, 3, 0, 1, 7);

        Button3 = new QPushButton(centralWidget);
        Button3->setObjectName(QString::fromUtf8("Button3"));

        gridLayout->addWidget(Button3, 2, 6, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Port:", nullptr));
        Button1->setText(QApplication::translate("MainWindow", "Start", nullptr));
        Button2->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        label_2->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Serwer Zatrzymane", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Serwer Uruchomiony", nullptr));
        label_4->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "Otrzymano od klienta", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Nadano od klienta", nullptr));
        label_7->setText(QString());
        label_14->setText(QApplication::translate("MainWindow", "Otrzymano od Bazy Danych", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Nadano od Bazy Danych", nullptr));
        label_3->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        checkBox->setText(QApplication::translate("MainWindow", "W\305\202\304\205cz Automatyczne Przewijanie", nullptr));
        Text1->setPlaceholderText(QString());
        Button3->setText(QApplication::translate("MainWindow", "Generuj Raport", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
