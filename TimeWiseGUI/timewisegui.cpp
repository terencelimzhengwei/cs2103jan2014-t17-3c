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

const char* ADD_FORMAT = "add: description start_date due_date start_time due_time !priority #category";
const char* DELETE_FORMAT = "delete: ID or all";
const char* DONE_FORMAT = "done: ID or #category";
const char* EDIT_FORMAT = "edit: ID header contents";
const char* FILTER_FORMAT = "filter: #category";
const char* FIND_FORMAT = "find: keywords";
const char* DEFAULT_DISPLAY = "List of Commands: add, delete, done, edit, filter, find, undo, redo";

TimeWiseGUI::TimeWiseGUI(QWidget *parent): QMainWindow(parent) {
	ui.setupUi(this);

	//set up tableView
	model = new QStandardItemModel (0, 5, this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Description")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Start Date")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Due Date")));
	model->setHorizontalHeaderItem(3, new QStandardItem(QString("Start Time")));
	model->setHorizontalHeaderItem(4, new QStandardItem(QString("Due Time")));
	model->setHorizontalHeaderItem(5, new QStandardItem(QString("Pri")));
	model->setHorizontalHeaderItem(6, new QStandardItem(QString("Category")));
	ui.tableView->setModel(model);
	
	//allows long texts to be wrapped.
	ui.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//set column widths of table. Hardcoded and very primitive.
	ui.tableView->setColumnWidth(0, 240);
	ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(1, 70);
	ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(2, 70);
	ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(3, 70);
	ui.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(4, 70);
	ui.tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(5, 40);
	ui.tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(6, 80);
	ui.tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
	ui.tableView->setMinimumWidth(700);
	ui.tableView->setMaximumWidth(700);

	//set up row heights of table.
	ui.tableView->verticalHeader()->setDefaultSectionSize(27);

	this->setWindowFlags(Qt::CustomizeWindowHint);

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
	fontDatabase.addApplicationFont(":/TimeWiseGUI/CFJackStory-Regular.ttf");
	fontDatabase.addApplicationFont(":/TimeWiseGUI/Homestead Display.ttf");
	fontDatabase.addApplicationFont(":/TimeWiseGUI/EHSMB.TTF");
	fontDatabase.addApplicationFont(":/TimeWiseGUI/comesinhandy.ttf");

	ui.label_date->setFont(QFont("Electronic Highway Sign",19,75));
	ui.label_time->setFont(QFont("Electronic Highway Sign",14,75));
	ui.tableView->horizontalHeader()->setFont(QFont("CF Jack Story",11,75));
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
	
	setData();

	QString outputMessage = QString::fromStdString(messageLog);
	ui.label_mlog->setText(outputMessage);

	ui.userInput->clear();
}

void TimeWiseGUI::setData() {
	//clears the contents in the table before displaying updated taskList
	model->removeRows(0, model->rowCount());
	
	TaskList taskList = _logic.getTaskList();
	for(int i = 0; i < taskList.size(); i++) {
		for(int j = 0; j < 7; j++) {
			//add row for every task in taskList dynamically
			model->setRowCount(i+1);

			switch (j) {
			case 0: {
				std::string taskDescription = (taskList.getTask(i))->getDescription();
				QString qTask = QString::fromStdString(taskDescription);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			case 1: {
				std::string taskStartDate = taskList.getTask(i)->getStartDate()->toString();
				QString qTask = QString::fromStdString(taskStartDate);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}/*
			case 2: {
				std::string taskEndDate = taskList.getTask(i)->getEndDate()->toString();
				QString qTask = QString::fromStdString(taskEndDate);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			case 3: {
				std::string taskStartTime = taskList.getTask(i)->getStartTime()->toString();
				QString qTask = QString::fromStdString(taskStartTime);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			case 4: {
				std::string taskEndTime = taskList.getTask(i)->getEndTime()->toString();
				QString qTask = QString::fromStdString(taskEndTime);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			case 5: {
				PRIORITY taskPriority = taskList.getTask(i)->getPriority();
				QString qTask = QString::fromStdString(PRIORITY_STRING[taskPriority]);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}*/
			case 6: {
				std::string taskCategory= taskList.getTask(i)->getTaskCategory();
				QString qTask = QString::fromStdString(taskCategory);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			}
		}
	}
}