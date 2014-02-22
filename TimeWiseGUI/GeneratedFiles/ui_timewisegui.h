/********************************************************************************
** Form generated from reading UI file 'timewisegui.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeWiseGUIClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QLabel *label_task;
    QLabel *label_mlog;
    QLabel *label_help;
    QLabel *label_desc;
    QTableView *tableView;
    QLabel *label_logo;
    QLabel *label_date;
    QLabel *label_time;

    void setupUi(QMainWindow *TimeWiseGUIClass)
    {
        if (TimeWiseGUIClass->objectName().isEmpty())
            TimeWiseGUIClass->setObjectName(QStringLiteral("TimeWiseGUIClass"));
        TimeWiseGUIClass->resize(802, 436);
        TimeWiseGUIClass->setMinimumSize(QSize(802, 436));
        TimeWiseGUIClass->setMaximumSize(QSize(802, 436));
        TimeWiseGUIClass->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(TimeWiseGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 390, 601, 20));
        lineEdit->setMinimumSize(QSize(601, 20));
        lineEdit->setMaximumSize(QSize(800, 20));
        label_task = new QLabel(centralWidget);
        label_task->setObjectName(QStringLiteral("label_task"));
        label_task->setGeometry(QRect(20, 10, 181, 51));
        label_task->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"font: 75 italic 42pt \"Christopherhand\";"));
        label_mlog = new QLabel(centralWidget);
        label_mlog->setObjectName(QStringLiteral("label_mlog"));
        label_mlog->setGeometry(QRect(10, 410, 251, 16));
        label_help = new QLabel(centralWidget);
        label_help->setObjectName(QStringLiteral("label_help"));
        label_help->setGeometry(QRect(10, 370, 371, 16));
        label_desc = new QLabel(centralWidget);
        label_desc->setObjectName(QStringLiteral("label_desc"));
        label_desc->setGeometry(QRect(10, 350, 241, 16));
        label_desc->setStyleSheet(QLatin1String("font: 75 12pt \"Rockwell Condensed\";\n"
"color: rgb(170, 0, 0);"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 70, 781, 271));
        label_logo = new QLabel(centralWidget);
        label_logo->setObjectName(QStringLiteral("label_logo"));
        label_logo->setGeometry(QRect(620, 370, 181, 51));
        label_logo->setStyleSheet(QStringLiteral("background-image: url(:/TimeWiseGUI/123.jpg);"));
        label_date = new QLabel(centralWidget);
        label_date->setObjectName(QStringLiteral("label_date"));
        label_date->setGeometry(QRect(510, 10, 291, 31));
        label_date->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"font: 75 26pt \"Homestead Display\";"));
        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(690, 40, 101, 21));
        label_time->setStyleSheet(QLatin1String("font: 75 20pt \"Homestead Display\";\n"
"color: rgb(255, 170, 0);"));
        TimeWiseGUIClass->setCentralWidget(centralWidget);

        retranslateUi(TimeWiseGUIClass);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), TimeWiseGUIClass, SLOT(lineEditReturnPressed()));

        QMetaObject::connectSlotsByName(TimeWiseGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *TimeWiseGUIClass)
    {
        TimeWiseGUIClass->setWindowTitle(QApplication::translate("TimeWiseGUIClass", "TimeWiseGUI", 0));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("TimeWiseGUIClass", "<html><head/><body><p>input commands here.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("TimeWiseGUIClass", "+ Add Task", 0));
        label_task->setText(QApplication::translate("TimeWiseGUIClass", "Your Tasks", 0));
        label_mlog->setText(QApplication::translate("TimeWiseGUIClass", "Welcome to TiMEWiSE!", 0));
        label_help->setText(QApplication::translate("TimeWiseGUIClass", "add <task description><duedate><category><priority>", 0));
        label_desc->setText(QApplication::translate("TimeWiseGUIClass", "What would you like to do today?", 0));
        label_logo->setText(QString());
        label_date->setText(QApplication::translate("TimeWiseGUIClass", "SAT 20 feb 2014", 0));
        label_time->setText(QApplication::translate("TimeWiseGUIClass", "13:20:20", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeWiseGUIClass: public Ui_TimeWiseGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEWISEGUI_H
