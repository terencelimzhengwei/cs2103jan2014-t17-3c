#include "timewisegui.h"

const char* ADD_COMMAND = "add";
const char* DELETE_COMMAND = "delete";
const char* DONE_COMMAND = "done";
const char* EDIT_COMMAND = "edit";
const char* FILTER_COMMAND = "filter";
const char* FIND_COMMAND = "find";

const char* ADD_FORMAT = "add: 'description' due_date due_time !priority #category";
const char* DELETE_FORMAT = "delete: ID or all";
const char* DONE_FORMAT = "done: ID or #category";
const char* EDIT_FORMAT = "edit: ID header contents";
const char* FILTER_FORMAT = "filter: #category";
const char* FIND_FORMAT = "find: keywords";
const char* DEFAULT_DISPLAY = "List of Commands: add, delete, done, edit, filter, find";

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

void TimeWiseGUI::updateTime() {
	QDate date = QDate::currentDate();
	ui.label_date->setText(date.toString());
	QTime time = QTime::currentTime();
	ui.label_time->setText(time.toString());
}

void TimeWiseGUI::on_userInput_textChanged() {
	if(ui.userInput->text() == ADD_COMMAND) {
		ui.label_help->setText(ADD_FORMAT);
	} else if(ui.userInput->text() == DELETE_COMMAND) {
		ui.label_help->setText(DELETE_FORMAT);
	} else if(ui.userInput->text() == DONE_COMMAND) {
		ui.label_help->setText(DONE_FORMAT);
	} else if(ui.userInput->text() == EDIT_COMMAND) {
		ui.label_help->setText(EDIT_FORMAT);
	} else if(ui.userInput->text() == FILTER_COMMAND) {
		ui.label_help->setText(FILTER_FORMAT);
	} else if(ui.userInput->text() == FIND_COMMAND) {
		ui.label_help->setText(FIND_FORMAT);
	} else if(ui.userInput->text() == "") {
		ui.label_help->setText(DEFAULT_DISPLAY);
	}
}

void TimeWiseGUI::on_userInput_returnPressed() {
	QString input = ui.userInput->text();
	//convert Qstring to string
	std::string userCommand = input.toLocal8Bit().constData();

	std::string messageLog = _logic.processCommand(userCommand);
	
	TaskList taskList = _logic.getTaskList();
	ostringstream outstr;
	for(int i = 0; i < taskList.size(); i++) {
		std::string taskDescription = (taskList.getTask(i)).getDescription();
		outstr << i+1 << ". " << taskDescription << endl;
	}
	string allTasks = outstr.str();
	//convert string to Qstring
	QString outputTasks = QString::fromStdString(allTasks);
	ui.textBrowser->setText(outputTasks);
	
	QString outputMessage = QString::fromStdString(messageLog);
	ui.label_mlog->setText(outputMessage);

	ui.userInput->clear();
}