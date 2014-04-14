//@author A0097330H
#ifndef TIMEWISECLOCK_H
#define TIMEWISECLOCK_H

//============================================================
// This class is responsible for configuring a clock object
// whose date and time will be displayed in the main ui.
//============================================================
#include <QDate>
#include <QString>
#include <QTime>

class TimeWiseClock {
public:
	TimeWiseClock();
	~TimeWiseClock();
	QString dateToString();
	QString timeToString();

private:
	QDate _date;
	QTime _time;
};
#endif

