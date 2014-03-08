#include "timewisegui.h"
#include "tableModel.h"
#include <stdio.h>
#include <qdatetime.h>
#include <QHeaderView>

const char* ADD_COMMAND = "add";
const char* DELETE_COMMAND = "delete";
const char* DONE_COMMAND = "done";
const char* EDIT_COMMAND = "edit";
const char* FILTER_COMMAND = "filter";
const char* FIND_COMMAND = "find";

//
const char* ADD_FORMAT = "add: 'description' due_date due_time !priority #category";
const char* DELETE_FORMAT = "delete: ID or all";
const char* DONE_FORMAT = "done: ID or #category";
const char* EDIT_FORMAT = "edit: ID header contents";
const char* FILTER_FORMAT = "filter: #category";
const char* FIND_FORMAT = "find: keywords";
const char* DEFAULT_DISPLAY = "List of Commands: add, delete, done, edit, filter, find";

TimeWiseGUI::TimeWiseGUI(QWidget *parent): QMainWindow(parent) {
	ui.setupUi(this);

	ui.tableView->setModel( table() );
	
	//set column widths. Hardcoded and very primitive.
	ui.tableView->setColumnWidth(0, 40);
	ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(1, 350);
	ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(2, 100);
	ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(3, 100);
	ui.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(4, 60);
	ui.tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(5, 100);
	ui.tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
	ui.tableView->setMinimumWidth(770);
	ui.tableView->setMaximumWidth(770);

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
	
	std::string userCommand = input.toLocal8Bit().constData();

	//displays task detail in the correct box of the table. Hardcoded and very primitive.
	std::string messageLog = _logic.processCommand(userCommand);
	TaskList taskList = _logic.getTaskList();
	for(int i = 0; i < taskList.size(); i++) {
		for(int j = 0; j < 2; j++) {
			if(j == 0) {
				QString numbering = QString::number(i+1);
				table()->setItem(i, j, numbering);
			} else {
				std::string taskDescription = (taskList.getTask(i))->getDescription();
				QString qTask = QString::fromStdString(taskDescription);
				table()->setItem(i, j, qTask);
			}
		}
	}

	QString outputMessage = QString::fromStdString(messageLog);
	ui.label_mlog->setText(outputMessage);

	ui.userInput->clear();
}