#ifndef TIMEWISEFEEDBACK_H
#define TIMEWISEFEEDBACK_H

#include <QWidget>
#include <QPainter>
#include <QFontDatabase>
#include "ui_timewisefeedback.h"

class TimeWiseFeedback : public QWidget
{
	Q_OBJECT

public:
	TimeWiseFeedback(QWidget *parent = 0);
	~TimeWiseFeedback();
	void setData(const QString &labelText);
	void paintEvent(QPaintEvent *pe);

private:
	Ui::TimeWiseFeedback ui;

};
#endif // TIMEWISEFEEDBACK_H
