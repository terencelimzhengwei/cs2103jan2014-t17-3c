#include "timewisegui.h"
#include "tableModel.h"
#include <stdio.h>
#include <qdatetime.h>
#include <QHeaderView>
#include <QShortcut>

const char* ADD_COMMAND = "add";
const char* CLEAR_COMMAND = "clear";
const char* DELETE_COMMAND = "delete";
const char* DISPLAY_COMMAND = "display";
const char* DONE_COMMAND = "done";
const char* EDIT_COMMAND = "edit";
const char* FILTER_COMMAND = "filter";
const char* SEARCH_COMMAND = "search";

const char* ADD_FORMAT = "add: description start_date due_date start_time due_time !priority #category";
const char* CLEAR_FORMAT = "clear or clear all";
const char* DELETE_FORMAT = "delete: ID or keywords";
const char* DISPLAY_FORMAT = "display: main or completed";
const char* DONE_FORMAT = "done: ID or #category";
const char* EDIT_FORMAT = "edit: ID";
const char* FILTER_FORMAT = "filter: dates or !priority or #category";
const char* SEARCH_FORMAT = "search: keywords";
const char* DEFAULT_DISPLAY = "List of Commands: add, clear, delete, display, done, edit, search, undo, redo";

TimeWiseGUI::TimeWiseGUI(QWidget *parent): QMainWindow(parent) {
	ui.setupUi(this);

	ui.userInput->installEventFilter(this);

	setupTable();

	//set cursor to userInput lineEdit as soon as program is opened.
	QTimer::singleShot(0, ui.userInput, SLOT(setFocus()));
	
	//remove title header of main window
	this->setWindowFlags(Qt::CustomizeWindowHint);

	setupClock();

	setupFont();

	setupHotKeys();

	autoComplete();
	
	if(numberOfOverdues() > 0) {
		setOverdueMessage(numberOfOverdues());
	}
}

TimeWiseGUI::~TimeWiseGUI() {
}

bool TimeWiseGUI::eventFilter(QObject* obj, QEvent *event) {
	if (obj == ui.userInput) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Up) {
				previous_line();
				return true;
			} else if(keyEvent->key() == Qt::Key_Down) {
				next_line();
				return true;
			}
		}
		return false;
	}
	return QMainWindow::eventFilter(obj, event);
}


void TimeWiseGUI::on_userInput_textChanged() {
	if(ui.userInput->text() == ADD_COMMAND) {
		ui.label_help->setText(ADD_FORMAT);
	} else if(ui.userInput->text() == CLEAR_COMMAND) {
		ui.label_help->setText(CLEAR_FORMAT);
	} else if(ui.userInput->text() == DELETE_COMMAND) {
		ui.label_help->setText(DELETE_FORMAT);
	} else if(ui.userInput->text() == DISPLAY_COMMAND) {
		ui.label_help->setText(DISPLAY_FORMAT);
	} else if(ui.userInput->text() == DONE_COMMAND) {
		ui.label_help->setText(DONE_FORMAT);
	} else if(ui.userInput->text() == EDIT_COMMAND) {
		ui.label_help->setText(EDIT_FORMAT);
	} else if(ui.userInput->text() == FILTER_COMMAND) {
		ui.label_help->setText(FILTER_FORMAT);
	} else if(ui.userInput->text() == SEARCH_COMMAND) {
		ui.label_help->setText(SEARCH_FORMAT);
	} else if(ui.userInput->text() == "") {
		ui.label_help->setText(DEFAULT_DISPLAY);
	}
}

void TimeWiseGUI::on_userInput_returnPressed() {
	QString input = ui.userInput->text();

	//Stores user inputs into a QStringList for retrieval later when key up or down is pressed
	lines << ui.userInput->text();
	current_line = lines.size();
	ui.userInput->setText("");
	emit lineExecuted(lines.back());

	try {
		checkEmpty(input);
		
		std::string userCommand = input.toLocal8Bit().constData();

		std::string messageLog = _logic.processCommand(userCommand);

		/*bool isEdit = _logic.getTaskList().checkEditStatus();

		if(isEdit) {
			QString qOrigAction = QString::fromStdString(_logic.getUserInput());
			ui.userInput->setText(qOrigAction);
			ui.userInput->selectAll();
			displayTaskList(_logic.getScreenToDisplay());
		}
		else {*/
		autoComplete();
		DISPLAY_TYPE displayType = _logic.getScreenToDisplay();
		displayTaskList(displayType);

		QString outputMessage = QString::fromStdString(messageLog);
		ui.label_mlog->setText(outputMessage);
	}
	catch(const std::invalid_argument& e) {
		ui.label_mlog->setText(e.what());
	}
}

int TimeWiseGUI::checkEmpty(QString input) {
	if(input.size() == 0) {
		throw std::invalid_argument( "cannot enter empty input!" );
	}
}

void TimeWiseGUI::displayTaskList(DISPLAY_TYPE displayType) {
	switch(displayType){
	case MAIN: {
		setMainData();
		ui.label_title->setText("Your Tasks");
		break;
	}
	case SEARCHED: {
		vector<Task*> taskList = _logic.getTaskList().getSearchResults();
		setData(taskList);
		ui.label_title->setText("Searched Tasks");
		break;
	}
	case COMPLETE:{
		vector<Task*> taskList = _logic.getTaskList().getCompletedTaskList();
		setData(taskList);
		ui.label_title->setText("Completed Tasks");
		break;
	}
	case FILTERED:{
		vector<Task*> taskList = _logic.getTaskList().getFilterResults();
		setData(taskList);
		ui.label_title->setText("Filtered Tasks");
		break;
	}
	}
}

void TimeWiseGUI::setMainData() {
	//clears the contents in the table before displaying updated taskList
	model->removeRows(0, model->rowCount());

	TaskList taskList = _logic.getTaskList();

	for(int i = 0; i < taskList.undoneSize(); i++) {
		TASK_STATUS taskStatus = taskList.getTask(i)->getTaskStatus();
		QString qStatus = QString::fromStdString(TASK_STATUS_STRING[taskStatus]);
		QColor rowColorOverdue(255, 0, 0, 50);
		QColor rowColorComplete(146, 255, 192);

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
				if(taskList.getTask(i)->getStartDate()!=NULL){
					std::string taskStartDate = taskList.getTask(i)->getStartDate()->toString();
					QString qTask = QString::fromStdString(taskStartDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 2: {
				if(taskList.getTask(i)->getEndDate()!=NULL){
					std::string taskEndDate = taskList.getTask(i)->getEndDate()->toString();
					QString qTask = QString::fromStdString(taskEndDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 3: {
				if(taskList.getTask(i)->getStartTime()!=NULL){
					std::string taskStartTime = taskList.getTask(i)->getStartTime()->toString();
					QString qTask = QString::fromStdString(taskStartTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 4: {
				if(taskList.getTask(i)->getEndTime()!=NULL){
					std::string taskEndTime = taskList.getTask(i)->getEndTime()->toString();
					QString qTask = QString::fromStdString(taskEndTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 5: {
				PRIORITY taskPriority = taskList.getTask(i)->getPriority();
				QString qTask = QString::fromStdString(PRIORITY_STRING[taskPriority]);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			case 6: {
				if(taskList.getTask(i)->getTaskCategory()!=""){
					std::string taskCategory= taskList.getTask(i)->getTaskCategory();
					QString qTask = QString::fromStdString(taskCategory);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			}
			//highlight description in red if that task is overdue
			if(qStatus == "overdue") {
				model->setData(model->index(i, j), rowColorOverdue, Qt::BackgroundRole);
			}
			if (qStatus == "done") {
				model->setData(model->index(i, j), rowColorComplete, Qt::BackgroundRole);
			}
		}
	}
}

void TimeWiseGUI::setData(std::vector<Task*>& taskList)
{
	//clears the contents in the table before displaying updated taskList
	model->removeRows(0, model->rowCount());

	for(int i = 0; i < taskList.size(); i++) {
		TASK_STATUS taskStatus = taskList[i]->getTaskStatus();
		QString qStatus = QString::fromStdString(TASK_STATUS_STRING[taskStatus]);
		QColor rowColorOverdue(255, 0, 0, 50);
		QColor rowColorComplete(146, 255, 192);

		for(int j = 0; j < 7; j++) {
			//add row for every task in taskList dynamically
			model->setRowCount(i+1);

			switch (j) {
			case 0: {
				std::string taskDescription = (taskList[i])->getDescription();

				QString qTask = QString::fromStdString(taskDescription);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			case 1: {
				if(taskList[i]->getStartDate()!=NULL){
					std::string taskStartDate = taskList[i]->getStartDate()->toString();
					QString qTask = QString::fromStdString(taskStartDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 2: {
				if(taskList[i]->getEndDate()!=NULL){
					std::string taskEndDate = taskList[i]->getEndDate()->toString();
					QString qTask = QString::fromStdString(taskEndDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 3: {
				if(taskList[i]->getStartTime()!=NULL){
					std::string taskStartTime = taskList[i]->getStartTime()->toString();
					QString qTask = QString::fromStdString(taskStartTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 4: {
				if(taskList[i]->getEndTime()!=NULL){
					std::string taskEndTime = taskList[i]->getEndTime()->toString();
					QString qTask = QString::fromStdString(taskEndTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			case 5: {
				PRIORITY taskPriority = taskList[i]->getPriority();
				QString qTask = QString::fromStdString(PRIORITY_STRING[taskPriority]);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(i, j, item);
				break;
			}
			case 6: {
				if(taskList[i]->getTaskCategory()!=""){
					std::string taskCategory= taskList[i]->getTaskCategory();
					QString qTask = QString::fromStdString(taskCategory);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(i, j, item);
				}
				break;
			}
			}
			//highlight description in red if that task is overdue
			if(qStatus == "overdue") {
				model->setData(model->index(i, j), rowColorOverdue, Qt::BackgroundRole);
			} 
			if (qStatus == "done") {
				model->setData(model->index(i, j), rowColorComplete, Qt::BackgroundRole);
			}
		}
	}
}


//set up tableView
void TimeWiseGUI::setupTable() {
	model = new QStandardItemModel (0, 5, this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Description")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Start Date")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Due Date")));
	model->setHorizontalHeaderItem(3, new QStandardItem(QString("Start Time")));
	model->setHorizontalHeaderItem(4, new QStandardItem(QString("Due Time")));
	model->setHorizontalHeaderItem(5, new QStandardItem(QString("Pri")));
	model->setHorizontalHeaderItem(6, new QStandardItem(QString("Category")));
	setMainData();
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
	ui.tableView->setColumnWidth(5, 55);
	ui.tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(6, 65);
	ui.tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
	ui.tableView->setMinimumWidth(700);
	ui.tableView->setMaximumWidth(700);

	//set up row heights of table.
	ui.tableView->verticalHeader()->setDefaultSectionSize(27);

	//enable table to scroll to the bottom whenever a new row is inserted.
	connect(ui.tableView->model(), SIGNAL(rowsInserted (const QModelIndex &, int, int )), ui.tableView, SLOT(scrollToBottom ()));
}

//set date and time
void TimeWiseGUI::setupClock() {	
	QDate date = QDate::currentDate();
	ui.label_date->setText(date.toString());
	QTime time = QTime::currentTime();
	ui.label_time->setText(time.toString());

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT( updateTime() ));
	timer->start(1000);
}

void TimeWiseGUI::updateTime() {
	QDate date = QDate::currentDate();
	ui.label_date->setText(date.toString());
	QTime time = QTime::currentTime();
	ui.label_time->setText(time.toString());
 	if(_logic.getTaskList().checkNewOverdue()){
		_logic.getTaskList().updateOverdueTaskList();
		if(_logic.getScreenToDisplay()==MAIN){
			setMainData();
		}
	}
}

//font setting
void TimeWiseGUI::setupFont(){
	QFontDatabase fontDatabase; 
	fontDatabase.addApplicationFont(":/TimeWiseGUI/CFJackStory-Regular.ttf");
	fontDatabase.addApplicationFont(":/TimeWiseGUI/Homestead Display.ttf");
	fontDatabase.addApplicationFont(":/TimeWiseGUI/EHSMB.TTF");
	fontDatabase.addApplicationFont(":/TimeWiseGUI/comesinhandy.ttf");

	ui.label_date->setFont(QFont("Electronic Highway Sign",19,75));
	ui.label_time->setFont(QFont("Electronic Highway Sign",14,75));
	ui.tableView->horizontalHeader()->setFont(QFont("CF Jack Story",11,75));
}

//enable hotkeys
void TimeWiseGUI::setupHotKeys() {
	QShortcut *shortcutUndo = new QShortcut(QKeySequence("F3"), this);
	QShortcut *shortcutRedo = new QShortcut(QKeySequence("F4"), this);
	QShortcut *shortcutMain = new QShortcut(QKeySequence("F1"), this);
	QShortcut *shortcutDone = new QShortcut(QKeySequence("F2"), this);
	QObject::connect(shortcutUndo, SIGNAL(activated()), this, SLOT(undo()));
	QObject::connect(shortcutRedo, SIGNAL(activated()), this, SLOT(redo()));
	QObject::connect(shortcutMain, SIGNAL(activated()), this, SLOT(displayMain()));
	QObject::connect(shortcutDone, SIGNAL(activated()), this, SLOT(displayDone()));
}

void TimeWiseGUI::undo(){
	_logic.processCommand("undo");
	setMainData();
}

void TimeWiseGUI::redo(){
	_logic.processCommand("redo");
	setMainData();
}

void TimeWiseGUI::displayMain(){
	_logic.processCommand("display main");
	setMainData();
	ui.label_title->setText("Your Tasks");
}

void TimeWiseGUI::displayDone(){
	_logic.processCommand("display done");
	vector<Task*> taskList = _logic.getTaskList().getCompletedTaskList();
	setData(taskList);
	ui.label_title->setText("Completed Tasks");
}


void TimeWiseGUI::setOverdueMessage(int overdueCount) {
	QMessageBox overdueInfo;
	ostringstream outstr;
	
	outstr << "You have " << overdueCount << " overdue task(s).";
	std::string overdueReminder = outstr.str();
	QString qOverdue = QString::fromStdString(overdueReminder);

	overdueInfo.setText(qOverdue);
	overdueInfo.setIcon(QMessageBox::Information);
	overdueInfo.exec();
}

int TimeWiseGUI::numberOfOverdues() {
	TaskList taskList = _logic.getTaskList();
	std::vector<Task*> overdueTaskList = taskList.getOverdueTaskList();
	int overdueTasksCount = overdueTaskList.size(); 
	return overdueTasksCount;
}

//"auto-complete" for search functions
void TimeWiseGUI::autoComplete() {
	QStringList descList;
	TaskList taskList = _logic.getTaskList();

	for(int i = 0; i < taskList.undoneSize(); i++) {
		ostringstream outstrDesc;
		outstrDesc << SEARCH_COMMAND << " " << taskList.getTask(i)->getDescription();
		QString qDesc = QString::fromStdString(outstrDesc.str());
		descList << qDesc;
	}
	descCompleter = new QCompleter(descList, this);
	descCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	ui.userInput->setCompleter(descCompleter);
}

void TimeWiseGUI::wheelEvent(QWheelEvent *ev ) {
	if ( ev->delta() > 0 ) {
		previous_line();
	} else {
		next_line();
	}
}

void TimeWiseGUI::previous_line() {
	if ( lines.empty() )
		return;

	if ( !ui.userInput->text().isEmpty() 
		&& ( current_line >= lines.size() || ui.userInput->text() != lines[current_line] ) )
		unfinished = ui.userInput->text();

	if ( current_line > 0 )
		current_line--;

	ui.userInput->setText(lines[current_line]);
}


void TimeWiseGUI::next_line() {
	if ( lines.empty() ) {
		return;
	}

	current_line++;

	if ( current_line >= lines.size() ) {
		ui.userInput->setText(unfinished);
		unfinished = "";
		current_line = lines.size();
	} else {
		ui.userInput->setText(lines[current_line]);
	}
}