/********************************************************************************
** Form generated from reading UI file 'timewisefeedback.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeWiseFeedback
{
public:
    QLabel *userFeedback;
    QPushButton *pushButton_ok;

    void setupUi(QWidget *TimeWiseFeedback)
    {
        if (TimeWiseFeedback->objectName().isEmpty())
            TimeWiseFeedback->setObjectName(QStringLiteral("TimeWiseFeedback"));
        TimeWiseFeedback->resize(331, 333);
        TimeWiseFeedback->setMinimumSize(QSize(331, 333));
        TimeWiseFeedback->setMaximumSize(QSize(331, 333));
        TimeWiseFeedback->setStyleSheet(QStringLiteral("#TimeWiseFeedback{image: url(:/TimeWiseGUI/feedbackground.png);}"));
        userFeedback = new QLabel(TimeWiseFeedback);
        userFeedback->setObjectName(QStringLiteral("userFeedback"));
        userFeedback->setGeometry(QRect(70, 60, 191, 171));
        pushButton_ok = new QPushButton(TimeWiseFeedback);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(130, 280, 75, 23));
        pushButton_ok->setDefault(true);

        retranslateUi(TimeWiseFeedback);
        QObject::connect(pushButton_ok, SIGNAL(clicked()), TimeWiseFeedback, SLOT(close()));

        QMetaObject::connectSlotsByName(TimeWiseFeedback);
    } // setupUi

    void retranslateUi(QWidget *TimeWiseFeedback)
    {
        TimeWiseFeedback->setWindowTitle(QApplication::translate("TimeWiseFeedback", "TimeWiseFeedback", 0));
        userFeedback->setText(QString());
        pushButton_ok->setText(QApplication::translate("TimeWiseFeedback", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeWiseFeedback: public Ui_TimeWiseFeedback {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEWISEFEEDBACK_H
