//@Gian Jian Xiang A0097330H
#ifndef TIMEWISEHELP_H
#define TIMEWISEHELP_H

#include <QWidget>
#include <QPainter>
#include <QFontDatabase>
#include "ui_timewisehelp.h"
#include "Constants_ui.h"

class TimeWiseHelp : public QWidget
{
	Q_OBJECT

public:
	TimeWiseHelp(QWidget *parent = 0);
	~TimeWiseHelp();
	void paintEvent(QPaintEvent *pe);

private:
	Ui::TimeWiseHelp ui;

};
#endif TIMEWISEHELP_H
