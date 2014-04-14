//@author A0097330H
#ifndef TIMEWISEHELP_H
#define TIMEWISEHELP_H

#include <QFontDatabase>
#include <QPainter>
#include <QWidget>
#include "ui_timewisehelp.h"
#include "Constants_ui.h"
//============================================================
// This class is responsible for configuring a help-guide 
// object that is displayed when user keys in 'help' in main ui.
//============================================================

class TimeWiseHelp : public QWidget {
	Q_OBJECT

public:
	TimeWiseHelp(QWidget *parent = 0);
	~TimeWiseHelp();
	void paintEvent(QPaintEvent *pe);

private:
	Ui::TimeWiseHelp ui;

};
#endif TIMEWISEHELP_H
