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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeWiseGUIClass
{
public:
    QWidget *centralWidget;
    QTableView *tableView;
    QLabel *label_date;
    QLabel *label_time;
    QPushButton *pushButton_minimize;
    QPushButton *pushButton_close;
    QLabel *label_title;
    QLabel *label_help;
    QLineEdit *userInput;
    QLabel *label_mlog;
    QLabel *emptyLogo;

    void setupUi(QMainWindow *TimeWiseGUIClass)
    {
        if (TimeWiseGUIClass->objectName().isEmpty())
            TimeWiseGUIClass->setObjectName(QStringLiteral("TimeWiseGUIClass"));
        TimeWiseGUIClass->setWindowModality(Qt::NonModal);
        TimeWiseGUIClass->setEnabled(true);
        TimeWiseGUIClass->resize(600, 713);
        TimeWiseGUIClass->setMinimumSize(QSize(600, 713));
        TimeWiseGUIClass->setMaximumSize(QSize(600, 713));
        TimeWiseGUIClass->setAutoFillBackground(false);
        TimeWiseGUIClass->setStyleSheet(QStringLiteral("#TimeWiseGUIClass{image: url(:/TimeWiseGUI/new_TimeWise background.png);}"));
        centralWidget = new QWidget(TimeWiseGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(30, 120, 531, 401));
        QFont font;
        font.setFamily(QStringLiteral("New Cicle"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        tableView->setFont(font);
        tableView->setStyleSheet(QStringLiteral("font: 75 10pt \"New Cicle\";"));
        tableView->setFrameShape(QFrame::StyledPanel);
        tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableView->setAutoScroll(true);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(false);
        label_date = new QLabel(centralWidget);
        label_date->setObjectName(QStringLiteral("label_date"));
        label_date->setGeometry(QRect(330, 50, 211, 31));
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
        font1.setPointSize(17);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        label_date->setFont(font1);
        label_date->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 75 17pt \"Electronic Highway Sign\";"));
        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(330, 80, 141, 20));
        label_time->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 75 14pt \"Electronic Highway Sign\";"));
        pushButton_minimize = new QPushButton(centralWidget);
        pushButton_minimize->setObjectName(QStringLiteral("pushButton_minimize"));
        pushButton_minimize->setGeometry(QRect(490, 30, 30, 15));
        pushButton_minimize->setMinimumSize(QSize(30, 15));
        pushButton_minimize->setMaximumSize(QSize(30, 15));
        pushButton_minimize->setStyleSheet(QLatin1String("\n"
"background-color: transparent\n"
""));
        pushButton_close = new QPushButton(centralWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(520, 30, 30, 15));
        pushButton_close->setMinimumSize(QSize(30, 15));
        pushButton_close->setMaximumSize(QSize(30, 15));
        pushButton_close->setStyleSheet(QLatin1String("\n"
"background-color: transparent\n"
""));
        label_title = new QLabel(centralWidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(40, 50, 201, 31));
        label_title->setStyleSheet(QLatin1String("font: 75 26pt \"CF Jack Story\";\n"
"color: rgb(0, 85, 255);"));
        label_help = new QLabel(centralWidget);
        label_help->setObjectName(QStringLiteral("label_help"));
        label_help->setGeometry(QRect(50, 541, 501, 20));
        label_help->setStyleSheet(QStringLiteral("font: 75 10.5pt \"New Cicle\";"));
        label_help->setWordWrap(true);
        userInput = new QLineEdit(centralWidget);
        userInput->setObjectName(QStringLiteral("userInput"));
        userInput->setGeometry(QRect(50, 560, 491, 20));
        userInput->setStyleSheet(QStringLiteral("border-radius: 9px"));
        label_mlog = new QLabel(centralWidget);
        label_mlog->setObjectName(QStringLiteral("label_mlog"));
        label_mlog->setGeometry(QRect(40, 600, 291, 71));
        label_mlog->setStyleSheet(QLatin1String("font: 13pt \"CF Jack Story\";\n"
"color: rgb(0, 85, 255);"));
        label_mlog->setWordWrap(true);
        emptyLogo = new QLabel(centralWidget);
        emptyLogo->setObjectName(QStringLiteral("emptyLogo"));
        emptyLogo->setGeometry(QRect(80, 230, 421, 171));
        emptyLogo->setStyleSheet(QStringLiteral("image: url(:/TimeWiseGUI/Emptylogo.png);"));
        TimeWiseGUIClass->setCentralWidget(centralWidget);
        userInput->raise();
        pushButton_close->raise();
        tableView->raise();
        label_date->raise();
        label_time->raise();
        pushButton_minimize->raise();
        label_title->raise();
        label_help->raise();
        label_mlog->raise();
        emptyLogo->raise();

        retranslateUi(TimeWiseGUIClass);
        QObject::connect(pushButton_close, SIGNAL(clicked()), TimeWiseGUIClass, SLOT(close()));
        QObject::connect(pushButton_minimize, SIGNAL(clicked()), TimeWiseGUIClass, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(TimeWiseGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *TimeWiseGUIClass)
    {
        TimeWiseGUIClass->setWindowTitle(QApplication::translate("TimeWiseGUIClass", "TimeWiseGUI", 0));
        label_date->setText(QApplication::translate("TimeWiseGUIClass", "Date", 0));
        label_time->setText(QApplication::translate("TimeWiseGUIClass", "Time", 0));
        pushButton_minimize->setText(QString());
        pushButton_close->setText(QString());
        label_title->setText(QApplication::translate("TimeWiseGUIClass", "Your Tasks", 0));
        label_help->setText(QApplication::translate("TimeWiseGUIClass", "You may: Add, Clear, Delete, Display, Done, Edit, Filter, Search, Undo, Redo, Help, Exit", 0));
        userInput->setPlaceholderText(QApplication::translate("TimeWiseGUIClass", "+Add Task", 0));
        label_mlog->setText(QApplication::translate("TimeWiseGUIClass", "                      WELCOME TO...", 0));
        emptyLogo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TimeWiseGUIClass: public Ui_TimeWiseGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEWISEGUI_H
