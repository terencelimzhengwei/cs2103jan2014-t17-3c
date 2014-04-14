#ifndef TIMEWISEHELP_H
#define TIMEWISEHELP_H

//@author A0097330H
#include <QFontDatabase>
#include <QPainter>
#include <QWidget>
#include "ui_timewisehelp.h"
#include "Constants_ui.h"

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
