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
    QPushButton *pushButton_minimize;
    QPushButton *pushButton_close;
    QLabel *label_title;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_help;
    QLineEdit *userInput;

    void setupUi(QMainWindow *TimeWiseGUIClass)
    {
        if (TimeWiseGUIClass->objectName().isEmpty())
            TimeWiseGUIClass->setObjectName(QStringLiteral("TimeWiseGUIClass"));
        TimeWiseGUIClass->setWindowModality(Qt::NonModal);
        TimeWiseGUIClass->setEnabled(true);
        TimeWiseGUIClass->resize(600, 708);
        TimeWiseGUIClass->setMinimumSize(QSize(600, 708));
        TimeWiseGUIClass->setMaximumSize(QSize(600, 708));
        TimeWiseGUIClass->setAutoFillBackground(false);
        TimeWiseGUIClass->setStyleSheet(QStringLiteral("#TimeWiseGUIClass{image: url(:/TimeWiseGUI/new_TimeWise background.png);}"));
        centralWidget = new QWidget(TimeWiseGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(30, 120, 531, 391));
        QFont font;
        font.setFamily(QStringLiteral("Leelawadee"));
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        tableView->setFont(font);
        tableView->setStyleSheet(QStringLiteral("font: 75 9pt \"Leelawadee\";"));
        tableView->setFrameShape(QFrame::StyledPanel);
        tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableView->setAutoScroll(true);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label_date = new QLabel(centralWidget);
        label_date->setObjectName(QStringLiteral("label_date"));
        label_date->setGeometry(QRect(330, 40, 211, 31));
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
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        label_date->setFont(font1);
        label_date->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 75 18pt \"Electronic Highway Sign\";"));
        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(330, 70, 141, 20));
        label_time->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 75 14pt \"Electronic Highway Sign\";"));
        pushButton_minimize = new QPushButton(centralWidget);
        pushButton_minimize->setObjectName(QStringLiteral("pushButton_minimize"));
        pushButton_minimize->setGeometry(QRect(560, 0, 21, 20));
        pushButton_minimize->setStyleSheet(QLatin1String("font: 75 6pt \"Impact\";\n"
"background-color: transparent\n"
"rgb(255, 0, 0)"));
        pushButton_close = new QPushButton(centralWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(580, 0, 21, 20));
        pushButton_close->setStyleSheet(QLatin1String("font: 75 11pt \"MS Shell Dlg 2\";\n"
"background-color: transparent\n"
"rgb(255, 0, 0)"));
        label_title = new QLabel(centralWidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(50, 50, 201, 31));
        label_title->setStyleSheet(QLatin1String("font: 75 26pt \"CF Jack Story\";\n"
"color: rgb(0, 85, 255);"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 530, 501, 61));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_help = new QLabel(widget);
        label_help->setObjectName(QStringLiteral("label_help"));
        label_help->setStyleSheet(QStringLiteral("font: 75 10pt \"Leelawadee\";"));
        label_help->setWordWrap(true);

        verticalLayout->addWidget(label_help);

        userInput = new QLineEdit(widget);
        userInput->setObjectName(QStringLiteral("userInput"));

        verticalLayout->addWidget(userInput);

        TimeWiseGUIClass->setCentralWidget(centralWidget);
        pushButton_close->raise();
        tableView->raise();
        label_date->raise();
        label_time->raise();
        pushButton_minimize->raise();
        label_title->raise();
        label_help->raise();

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
        pushButton_minimize->setText(QApplication::translate("TimeWiseGUIClass", "_", 0));
        pushButton_close->setText(QApplication::translate("TimeWiseGUIClass", "X", 0));
        label_title->setText(QApplication::translate("TimeWiseGUIClass", "Your Tasks", 0));
        label_help->setText(QApplication::translate("TimeWiseGUIClass", "List of Commands: add, block, clear, confirm, delete, display, done, edit, filter, search, undo, redo", 0));
        userInput->setPlaceholderText(QApplication::translate("TimeWiseGUIClass", "+Add Task", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeWiseGUIClass: public Ui_TimeWiseGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEWISEGUI_H
