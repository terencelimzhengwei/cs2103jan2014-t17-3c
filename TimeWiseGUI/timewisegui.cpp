#include "timewisegui.h"

TimeWiseGUI::TimeWiseGUI(QWidget *parent)
	: QMainWindow(parent) {
	ui.setupUi(this);

	//set date and time
	QDate date = QDate::currentDate();
	ui.label_date->setText(date.toString());
	QTime time = QTime::currentTime();
	ui.label_time->setText(time.toString());

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT( updateTime() ));
	timer->start(1000);

	//font setting
	QFontDatabase fontDatabase; 
	fontDatabase.addApplicationFont(":/comesinhandy.ttf");
	fontDatabase.addApplicationFont(":/Homestead Display.ttf");
}

TimeWiseGUI::~TimeWiseGUI() {
}

void TimeWiseGUI::lineEditReturnPressed(){
	ui.userInput->clear();
}

void TimeWiseGUI::updateTime() {
	QDate date = QDate::currentDate();
	ui.label_date->setText(date.toString());
	QTime time = QTime::currentTime();
	ui.label_time->setText(time.toString());
}

void TimeWiseGUI::on_userInput_textChanged() {
	if(ui.userInput->text() == "add") {
		ui.label_help->setText("add: 'description' <due date> <due time> !priority #category");
	} else if(ui.userInput->text() == "delete") {
		ui.label_help->setText("delete: <ID> or delete all");
	} else if(ui.userInput->text() == "done") {
		ui.label_help->setText("done: <ID> or done #category");
	} else if(ui.userInput->text() == "find") {
		ui.label_help->setText("find: <keywords>");
	} else if(ui.userInput->text() == "filter") {
		ui.label_help->setText("filter: #category");
	} else if(ui.userInput->text() == "edit") {
		ui.label_help->setText("edit: <ID> <header> <contents>");
	} else if(ui.userInput->text() == "") {
		ui.label_help->setText("List of Commands: add, delete, done, edit, filter, find");
	}
}