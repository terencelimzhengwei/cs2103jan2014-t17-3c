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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeWiseGUIClass
{
public:
    QWidget *centralWidget;
    QLabel *label_task;
    QLabel *label_date;
    QLabel *label_time;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_desc;
    QLabel *label_help;
    QLineEdit *userInput;
    QLabel *label_mlog;
    QLabel *label;

    void setupUi(QMainWindow *TimeWiseGUIClass)
    {
        if (TimeWiseGUIClass->objectName().isEmpty())
            TimeWiseGUIClass->setObjectName(QStringLiteral("TimeWiseGUIClass"));
        TimeWiseGUIClass->resize(815, 436);
        TimeWiseGUIClass->setMinimumSize(QSize(802, 436));
        TimeWiseGUIClass->setMaximumSize(QSize(815, 436));
        TimeWiseGUIClass->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(TimeWiseGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_task = new QLabel(centralWidget);
        label_task->setObjectName(QStringLiteral("label_task"));
        label_task->setGeometry(QRect(20, 0, 171, 51));
        label_task->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"font: italic 45pt \"Christopherhand\";"));
        label_date = new QLabel(centralWidget);
        label_date->setObjectName(QStringLiteral("label_date"));
        label_date->setGeometry(QRect(520, 10, 271, 31));
        label_date->setStyleSheet(QLatin1String("color: rgb(0, 0, 127);\n"
"font: 75 26pt \"Homestead Display\";"));
        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(700, 40, 111, 21));
        label_time->setStyleSheet(QLatin1String("font: 75 20pt \"Homestead Display\";\n"
"color: rgb(255, 170, 0);"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(11, 61, 791, 271));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 343, 796, 87));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_desc = new QLabel(layoutWidget);
        label_desc->setObjectName(QStringLiteral("label_desc"));
        label_desc->setStyleSheet(QLatin1String("font: 75 12pt \"Rockwell Condensed\";\n"
"color: rgb(170, 0, 0);"));

        verticalLayout->addWidget(label_desc);

        label_help = new QLabel(layoutWidget);
        label_help->setObjectName(QStringLiteral("label_help"));

        verticalLayout->addWidget(label_help);

        userInput = new QLineEdit(layoutWidget);
        userInput->setObjectName(QStringLiteral("userInput"));
        userInput->setMinimumSize(QSize(601, 20));
        userInput->setMaximumSize(QSize(800, 20));

        verticalLayout->addWidget(userInput);

        label_mlog = new QLabel(layoutWidget);
        label_mlog->setObjectName(QStringLiteral("label_mlog"));

        verticalLayout->addWidget(label_mlog);


        horizontalLayout->addLayout(verticalLayout);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/TimeWiseGUI/123.jpg")));

        horizontalLayout->addWidget(label);

        TimeWiseGUIClass->setCentralWidget(centralWidget);
        layoutWidget->raise();
        label_task->raise();
        label_date->raise();
        label_time->raise();
        tabWidget->raise();

        retranslateUi(TimeWiseGUIClass);
        QObject::connect(userInput, SIGNAL(textChanged(QString)), TimeWiseGUIClass, SLOT(on_userInput_textChanged()));
        QObject::connect(userInput, SIGNAL(returnPressed()), TimeWiseGUIClass, SLOT(on_userInput_returnPressed()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TimeWiseGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *TimeWiseGUIClass)
    {
        TimeWiseGUIClass->setWindowTitle(QApplication::translate("TimeWiseGUIClass", "TimeWiseGUI", 0));
        label_task->setText(QApplication::translate("TimeWiseGUIClass", "Your Tasks", 0));
        label_date->setText(QApplication::translate("TimeWiseGUIClass", "SAT 20 feb 2014", 0));
        label_time->setText(QApplication::translate("TimeWiseGUIClass", "13:20:20", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("TimeWiseGUIClass", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("TimeWiseGUIClass", "Tab 2", 0));
        label_desc->setText(QApplication::translate("TimeWiseGUIClass", "What would you like to do today?", 0));
        label_help->setText(QApplication::translate("TimeWiseGUIClass", "List of Commands: add, delete, done, edit, filter, find", 0));
#ifndef QT_NO_TOOLTIP
        userInput->setToolTip(QApplication::translate("TimeWiseGUIClass", "<html><head/><body><p>input commands here.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        userInput->setText(QString());
        userInput->setPlaceholderText(QApplication::translate("TimeWiseGUIClass", "+ Add Task", 0));
        label_mlog->setText(QApplication::translate("TimeWiseGUIClass", "Welcome to TiMEWiSE!", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TimeWiseGUIClass: public Ui_TimeWiseGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEWISEGUI_H
