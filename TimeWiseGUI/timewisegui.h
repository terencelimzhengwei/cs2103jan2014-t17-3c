#ifndef TIMEWISEGUI_H
#define TIMEWISEGUI_H

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <QTimer>
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

private:
	Ui::TimeWiseGUIClass ui;
};

#endif // TIMEWISEGUI_H
