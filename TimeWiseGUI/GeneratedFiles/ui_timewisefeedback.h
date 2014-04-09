/********************************************************************************
** Form generated from reading UI file 'timewisefeedback.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEWISEFEEDBACK_H
#define UI_TIMEWISEFEEDBACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeWiseFeedback
{
public:
    QPushButton *pushButton_ok;
    QTextEdit *textEdit;
    QLabel *label;

    void setupUi(QWidget *TimeWiseFeedback)
    {
        if (TimeWiseFeedback->objectName().isEmpty())
            TimeWiseFeedback->setObjectName(QStringLiteral("TimeWiseFeedback"));
        TimeWiseFeedback->resize(450, 565);
        TimeWiseFeedback->setMinimumSize(QSize(450, 565));
        TimeWiseFeedback->setMaximumSize(QSize(450, 565));
        TimeWiseFeedback->setStyleSheet(QStringLiteral("#TimeWiseFeedback{image: url(:/TimeWiseGUI/feedbackground.png);}"));
        pushButton_ok = new QPushButton(TimeWiseFeedback);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(190, 510, 75, 23));
        pushButton_ok->setDefault(true);
        textEdit = new QTextEdit(TimeWiseFeedback);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(40, 100, 370, 392));
        textEdit->setMinimumSize(QSize(370, 392));
        textEdit->setMaximumSize(QSize(370, 392));
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setReadOnly(true);
        label = new QLabel(TimeWiseFeedback);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 60, 141, 31));
        label->setStyleSheet(QLatin1String("font: 75 26pt \"CF Jack Story\";\n"
"color: rgb(0, 85, 255);"));

        retranslateUi(TimeWiseFeedback);
        QObject::connect(pushButton_ok, SIGNAL(clicked()), TimeWiseFeedback, SLOT(close()));

        QMetaObject::connectSlotsByName(TimeWiseFeedback);
    } // setupUi

    void retranslateUi(QWidget *TimeWiseFeedback)
    {
        TimeWiseFeedback->setWindowTitle(QApplication::translate("TimeWiseFeedback", "TimeWiseFeedback", 0));
        pushButton_ok->setText(QApplication::translate("TimeWiseFeedback", "OK", 0));
        textEdit->setHtml(QApplication::translate("TimeWiseFeedback", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/TimeWiseGUI/helpguide.png\" /></p></body></html>", 0));
        label->setText(QApplication::translate("TimeWiseFeedback", "Need Help?", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeWiseFeedback: public Ui_TimeWiseFeedback {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEWISEFEEDBACK_H
