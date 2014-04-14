#ifndef TIMEWISECLOCK_H
#define TIMEWISECLOCK_H

//@author A0097330H
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

