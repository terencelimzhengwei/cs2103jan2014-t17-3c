#ifndef TIMEWISEGUI_H
#define TIMEWISEGUI_H

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QFontDatabase>
#include "ui_timewisegui.h"


class TimeWiseGUI : public QMainWindow
{
	Q_OBJECT

public:
	TimeWiseGUI(QWidget *parent = 0);
	~TimeWiseGUI();

private slots:
	void lineEditReturnPressed();
	void updateTime();
	void on_userInput_textChanged();

private:
	Ui::TimeWiseGUIClass ui;
};

#endif // TIMEWISEGUI_H
