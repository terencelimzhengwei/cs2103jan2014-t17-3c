#ifndef TIMEWISEGUI_H
#define TIMEWISEGUI_H

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QFontDatabase>
#include <string>
#include "ui_timewisegui.h"
#include "TimeWiseLogic.h"


class TimeWiseGUI : public QMainWindow
{
	Q_OBJECT

public:
	TimeWiseGUI(QWidget *parent = 0);
	~TimeWiseGUI();

private slots:
	void updateTime();
	void on_userInput_textChanged();
	void on_userInput_returnPressed();

private:
	Ui::TimeWiseGUIClass ui;
	TimeWiseLogic _logic;
};

#endif // TIMEWISEGUI_H
