#ifndef TIMEWISECLOCK_H
#define TIMEWISECLOCK_H

#include <QString>
#include <QDate>
#include <QTime>

class TimeWiseClock {
public:
	TimeWiseClock();
	~TimeWiseClock();
	QString dateToString();
	QString timeToString();

private:
	QDate date;
	QTime time;
};

#endif

