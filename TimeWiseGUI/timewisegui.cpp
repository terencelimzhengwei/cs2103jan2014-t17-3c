#include "timewisegui.h"

TimeWiseGUI::TimeWiseGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//set date and time
	QDate date = QDate::currentDate();
	ui.label_date->setText(date.toString());
	QTime time = QTime::currentTime();
	ui.label_time->setText(time.toString());

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT( updateTime() ));
	timer->start(1000);
	

}

TimeWiseGUI::~TimeWiseGUI()
{

}

void TimeWiseGUI::lineEditReturnPressed(){
	ui.lineEdit->clear();
}

void TimeWiseGUI::updateTime()
{
	QDate date = QDate::currentDate();
	ui.label_date->setText(date.toString());
	QTime time = QTime::currentTime();
	ui.label_time->setText(time.toString());
}