/********************************************************************************
** Form generated from reading UI file 'timewisegui.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEWISEGUI_H
#define UI_TIMEWISEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeWiseGUIClass
{
public:
    QWidget *centralWidget;
    QTableView *tableView;
    QLabel *label_date;
    QLabel *label_time;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_help;
    QLineEdit *userInput;
    QLabel *label_mlog;

    void setupUi(QMainWindow *TimeWiseGUIClass)
    {
        if (TimeWiseGUIClass->objectName().isEmpty())
            TimeWiseGUIClass->setObjectName(QStringLiteral("TimeWiseGUIClass"));
        TimeWiseGUIClass->setWindowModality(Qt::NonModal);
        TimeWiseGUIClass->setEnabled(true);
        TimeWiseGUIClass->resize(815, 458);
        TimeWiseGUIClass->setMinimumSize(QSize(815, 458));
        TimeWiseGUIClass->setMaximumSize(QSize(815, 458));
        TimeWiseGUIClass->setAutoFillBackground(false);
        TimeWiseGUIClass->setStyleSheet(QStringLiteral("#TimeWiseGUIClass{image: url(:/TimeWiseGUI/Timewise background2.png);}"));
        centralWidget = new QWidget(TimeWiseGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(50, 111, 701, 191));
        QFont font;
        font.setFamily(QStringLiteral("CF Jack Story"));
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        tableView->setFont(font);
        tableView->setStyleSheet(QStringLiteral("font: 75 11pt \"CF Jack Story\";"));
        label_date = new QLabel(centralWidget);
        label_date->setObjectName(QStringLiteral("label_date"));
        label_date->setGeometry(QRect(511, 31, 241, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        label_date->setPalette(palette);
        QFont font1;
        font1.setFamily(QStringLiteral("Electronic Highway Sign"));
        font1.setPointSize(19);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        label_date->setFont(font1);
        label_date->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 75 19pt \"Electronic Highway Sign\";"));
        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(510, 60, 141, 20));
        label_time->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 75 14pt \"Electronic Highway Sign\";"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 360, 471, 70));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_help = new QLabel(layoutWidget);
        label_help->setObjectName(QStringLiteral("label_help"));
        label_help->setStyleSheet(QStringLiteral("font: 75 11pt \"Leelawadee\";"));

        verticalLayout->addWidget(label_help);

        userInput = new QLineEdit(layoutWidget);
        userInput->setObjectName(QStringLiteral("userInput"));

        verticalLayout->addWidget(userInput);

        label_mlog = new QLabel(layoutWidget);
        label_mlog->setObjectName(QStringLiteral("label_mlog"));
        label_mlog->setStyleSheet(QStringLiteral("font: 75 10pt \"Leelawadee\";"));

        verticalLayout->addWidget(label_mlog);

        TimeWiseGUIClass->setCentralWidget(centralWidget);

        retranslateUi(TimeWiseGUIClass);

        QMetaObject::connectSlotsByName(TimeWiseGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *TimeWiseGUIClass)
    {
        TimeWiseGUIClass->setWindowTitle(QApplication::translate("TimeWiseGUIClass", "TimeWiseGUI", 0));
        label_date->setText(QApplication::translate("TimeWiseGUIClass", "Date", 0));
        label_time->setText(QApplication::translate("TimeWiseGUIClass", "Time", 0));
        label_help->setText(QApplication::translate("TimeWiseGUIClass", "You may: Add, Delete, Done, Edit, Filter, Find", 0));
        label_mlog->setText(QApplication::translate("TimeWiseGUIClass", "Welcome to TIMEWiSE!", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeWiseGUIClass: public Ui_TimeWiseGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEWISEGUI_H
