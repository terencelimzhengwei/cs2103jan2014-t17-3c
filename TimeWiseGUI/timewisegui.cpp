#include "timewisegui.h"
#include <stdio.h>
#include <QHeaderView>
#include <QShortcut>

TimeWiseGUI::TimeWiseGUI(QWidget *parent): QMainWindow(parent) {
	ui.setupUi(this);

	configureTable();
	setupClock();
	setupFont();
	setupHotKeys();
	autoComplete();

	//set cursor to userInput box as soon as program is opened.
	QTimer::singleShot(NOUGHT, ui.userInput, SLOT(setFocus()));

	//remove title header of main window
	this->setWindowFlags(Qt::CustomizeWindowHint);

	ui.userInput->installEventFilter(this);

	//displays number of overdue tasks (if any) as soon as program is opened.
	int overdues = numberOfOverdues();
	if(overdues > 0) {
		setOverdueMessage(overdues);
	}
}

TimeWiseGUI::~TimeWiseGUI() {
}

//========================================================
//       USER INPUT BOX - WHEN TEXT CHANGES [SLOT]
//========================================================
//As user types in user input box, guide changes to show different command formats.
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
	} else if(ui.userInput->text() == BLANK) {
		ui.label_help->setText(DEFAULT_DISPLAY);
	}
}

//========================================================
//     USER INPUT BOX - WHEN 'ENTER' IS PRESSED [SLOT]
//========================================================
void TimeWiseGUI::on_userInput_returnPressed() {
	QString input = ui.userInput->text();

	if(input == HELP_COMMAND) {
		showHelp();
	} else if(input == EXIT_COMMAND) {
		exit(0);
	} else {
		//Stores user inputs into a QStringList for retrieval later when key up or down is pressed
		lines << input;
		current_line = lines.size();
		emit lineExecuted(lines.back());
		
		std::string userCommand = input.toLocal8Bit().constData();   //converts QString to string type.
		std::string messageLog = _logic.processCommand(userCommand); //sends user input (string) to logic for processing.
		QString outputMessage = QString::fromStdString(messageLog);  //converts string to QString type.
		ui.label_mlog->setText(outputMessage);                       //displays feedback.

		autoComplete();

		DISPLAY_TYPE displayType = _logic.getScreenToDisplay();
		displayTaskList(displayType);
	}
	ui.userInput->setText(BLANK);
}

//========================================================
//				MANAGE PAGE TO DISPLAY
//		[Main, Search, Filtered, Completed]
//========================================================

void TimeWiseGUI::displayTaskList(DISPLAY_TYPE displayType) {
	switch(displayType){
	case MAIN: {
		createMainTable();
		ui.label_title->setText(MAIN_TITLE);
		break;
	}
	case SEARCHED: {
		vector<Task*> taskList = _logic.getTaskList().getSearchResults();
		createOtherTables(taskList);
		ui.label_title->setText(SEARCHED_TITLE);
		break;
	}
	case COMPLETE:{
		vector<Task*> taskList = _logic.getTaskList().getCompletedTaskList();
		createOtherTables(taskList);
		ui.label_title->setText(COMPLETED_TITLE);
		break;
	}
	case FILTERED:{
		vector<Task*> taskList = _logic.getTaskList().getFilterResults();
		createOtherTables(taskList);
		ui.label_title->setText(FILTERED_TITLE);
		break;
	}
	}
}

//========================================================
//			MANAGES DATA AND SET IT INTO TABLE 
//						(MAIN PAGE)
//========================================================
void TimeWiseGUI::createMainTable() {
	//clears the contents in the table before displaying updated taskList
	model->removeRows(NOUGHT, model->rowCount());

	TaskList taskList = _logic.getTaskList();
	vector<int> latestIndices;
	
	//displays an image if table is empty; else, conceal it.
	if(taskList.undoneSize() == NOUGHT) {
		ui.emptyLogo->show();
	} else {
		ui.emptyLogo->hide();
	}

	setMainData(taskList, latestIndices);
	
	//scrolls to latest task after all tasks have been set in table.
	if(!latestIndices.empty()) {
		ui.tableView->scrollTo(model->index(latestIndices[NOUGHT], NOUGHT));
	}
}

//puts the data in place in the table. Bolds/highlights rows, if necessary
void TimeWiseGUI::setMainData(TaskList& taskList, vector<int>& latestIndices) {
	
	latestIndices = taskList.getLastTaskIndexList();
	
	//goes through each cell in the table and sets every attributes of every task into the respective cells.
	for(int row = 0; row < taskList.undoneSize(); row++) {
		for(int column = 0; column < COLUMN_COUNT; column++) {
			//add row for every task in taskList dynamically
			model->setRowCount(row + ADJUSTMENT_VALUE);

			switch (column) {
			case COLUMN_1: {
				std::string taskDescription = (taskList.getTask(row))->getDescription();
				QString qTask = QString::fromStdString(taskDescription);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(row, column, item);
				break;
			}
			case COLUMN_2: {
				std::string taskDay = taskList.getTask(row)->getDayString();
				QString qDay = QString::fromStdString(taskDay);
				QStandardItem* item = new QStandardItem(qDay);
				model->setItem(row, column, item);
				break;
			}
			case COLUMN_3: {
				if(taskList.getTask(row)->getStartDate()!=NULL){
					std::string taskStartDate = taskList.getTask(row)->getStartDate()->toString();
					QString qTask = QString::fromStdString(taskStartDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_4: {
				if(taskList.getTask(row)->getStartTime()!=NULL){
					std::string taskStartTime = taskList.getTask(row)->getStartTime()->toString();
					QString qTask = QString::fromStdString(taskStartTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_5: {
				if(taskList.getTask(row)->getEndDate()!=NULL){
					std::string taskEndDate = taskList.getTask(row)->getEndDate()->toString();
					QString qTask = QString::fromStdString(taskEndDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_6: {
				if(taskList.getTask(row)->getEndTime()!=NULL){
					std::string taskEndTime = taskList.getTask(row)->getEndTime()->toString();
					QString qTask = QString::fromStdString(taskEndTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_7: {
				if(taskList.getTask(row)->getTaskCategory()!= BLANK){
					std::string taskCategory= taskList.getTask(row)->getTaskCategory();
					QString qTask = QString::fromStdString(taskCategory);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			}
			//highlight description in red if status of that task is overdue, in green is status is done, and in yellow if status is clashed.
			TASK_STATUS taskStatus = taskList.getTask(row)->getTaskStatus();
			QString qStatus = QString::fromStdString(TASK_STATUS_STRING[taskStatus]);
			QColor rowColorOverdue(OVERDUE_R_INDEX, OVERDUE_G_INDEX, OVERDUE_B_INDEX, OVERDUE_TRANSPARENCY_INDEX);
			QColor rowColorComplete(COMPLETED_R_INDEX, COMPLETED_G_INDEX, COMPLETED_B_INDEX);
			QColor rowColorClash(CLASH_R_INDEX, CLASH_G_INDEX, CLASH_B_INDEX); 

			bool checkClash = taskList.getTask(row)->isClash();
			if(qStatus == OVERDUE_STATUS && checkClash) {
				model->setData(model->index(row, column), rowColorOverdue, Qt::BackgroundRole);
			} else if (qStatus == DONE_STATUS && checkClash) {
				model->setData(model->index(row, column), rowColorComplete, Qt::BackgroundRole);
			} else if (checkClash) {
				model->setData(model->index(row, column), rowColorClash, Qt::BackgroundRole);
			} else if(qStatus == OVERDUE_STATUS) {
				model->setData(model->index(row, column), rowColorOverdue, Qt::BackgroundRole);
			} else if (qStatus == DONE_STATUS) {
				model->setData(model->index(row, column), rowColorComplete, Qt::BackgroundRole);
			}

			//bolds entire task if it is the latest task added/edited. Also bolds existing task(s) that clashes with new task added/edited.
			QFont font;
			font.setBold(false);
			for(int i = 0; i < latestIndices.size(); i++) {
				if(row == latestIndices[i]) {
					font.setWeight(BOLDEST);
					font.setPointSize(BOLDED_FONT_SIZE);
				} 
			}
			model->setData(model->index(row,column), font, Qt::FontRole);
		}
	}
}

//========================================================
//			MANAGES DATA AND SET IT INTO TABLE
//		(OTHER PAGES - Searched, Filtered, Completed)
//========================================================
void TimeWiseGUI::createOtherTables(std::vector<Task*>& otherTaskList) {
	//clears the contents in the table before displaying updated taskList
	model->removeRows(NOUGHT, model->rowCount());
	ui.emptyLogo->hide();
	
	vector<int> latestIndices;
	setOtherData(otherTaskList, latestIndices);

	//scrolls to latest task after all tasks have been set in table.
	if(!latestIndices.empty()) {
		ui.tableView->scrollTo(model->index(latestIndices[NOUGHT], NOUGHT));
	}
}

void TimeWiseGUI::setOtherData(std::vector<Task*>& otherTaskList, vector<int>& latestIndices) {
	TaskList taskList = _logic.getTaskList();
	latestIndices = taskList.getLastTaskIndexList();

	for(int row = 0; row < otherTaskList.size(); row++) {
		for(int column = 0; column < COLUMN_COUNT; column++) {
			//add row for every task in taskList dynamically
			model->setRowCount(row+1);

			switch (column) {
			case COLUMN_1: {
				std::string taskDescription = (otherTaskList[row])->getDescription();
				QString qTask = QString::fromStdString(taskDescription);
				QStandardItem* item = new QStandardItem(qTask);
				model->setItem(row, column, item);
				break;
			}
			case COLUMN_2: {
				std::string taskDay = otherTaskList[row]->getDayString();
				QString qDay = QString::fromStdString(taskDay);
				QStandardItem* item = new QStandardItem(qDay);
				model->setItem(row, column, item);
				break;
			}
			case COLUMN_3: {			
				if(otherTaskList[row]->getStartDate()!=NULL){
					std::string taskStartDate = otherTaskList[row]->getStartDate()->toString();
					QString qTask = QString::fromStdString(taskStartDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_4: {
				if(otherTaskList[row]->getStartTime()!=NULL){
					std::string taskStartTime = otherTaskList[row]->getStartTime()->toString();
					QString qTask = QString::fromStdString(taskStartTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_5: {
				if(otherTaskList[row]->getEndDate()!=NULL){
					std::string taskEndDate = otherTaskList[row]->getEndDate()->toString();
					QString qTask = QString::fromStdString(taskEndDate);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_6: {
				if(otherTaskList[row]->getEndTime()!=NULL){
					std::string taskEndTime = otherTaskList[row]->getEndTime()->toString();
					QString qTask = QString::fromStdString(taskEndTime);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			case COLUMN_7: {
				if(otherTaskList[row]->getTaskCategory()!=""){
					std::string taskCategory= otherTaskList[row]->getTaskCategory();
					QString qTask = QString::fromStdString(taskCategory);
					QStandardItem* item = new QStandardItem(qTask);
					model->setItem(row, column, item);
				}
				break;
			}
			}
			//highlight row in red if status of that task is overdue, in green is status is done, and in yellow if status is clashed.
			TASK_STATUS taskStatus = otherTaskList[row]->getTaskStatus();
			QString qStatus = QString::fromStdString(TASK_STATUS_STRING[taskStatus]);
			QColor rowColorOverdue(OVERDUE_R_INDEX, OVERDUE_G_INDEX, OVERDUE_B_INDEX, OVERDUE_TRANSPARENCY_INDEX);
			QColor rowColorComplete(COMPLETED_R_INDEX, COMPLETED_G_INDEX, COMPLETED_B_INDEX);
			QColor rowColorClash(CLASH_R_INDEX, CLASH_G_INDEX, CLASH_B_INDEX); 

			bool checkClash = otherTaskList[row]->isClash();
			if(qStatus == OVERDUE_STATUS && checkClash) {
				model->setData(model->index(row, column), rowColorOverdue, Qt::BackgroundRole);
			} else if (qStatus == DONE_STATUS && checkClash) {
				model->setData(model->index(row, column), rowColorComplete, Qt::BackgroundRole);
			} else if (checkClash) {
				model->setData(model->index(row, column), rowColorClash, Qt::BackgroundRole);
			} else if(qStatus == OVERDUE_STATUS) {
				model->setData(model->index(row, column), rowColorOverdue, Qt::BackgroundRole);
			} else if (qStatus == DONE_STATUS) {
				model->setData(model->index(row, column), rowColorComplete, Qt::BackgroundRole);
			}

			//bolds entire task if it is the latest task added/edited. Also bolds existing task(s) that clashes with new task added/edited.
			QFont font;
			font.setBold(false);
			for(int i = 0; i < latestIndices.size(); i++) {
				if(row == latestIndices[i]) {
					font.setWeight(BOLDEST);
					font.setPointSize(BOLDED_FONT_SIZE);
				} 
			}
			model->setData(model->index(row,column), font, Qt::FontRole);
		}
	}
}


//=====================================================
//             TABLE INITIAL CONFIGURATION
//=====================================================

void TimeWiseGUI::configureTable() {
	//creates model and names column header titles
	model = new QStandardItemModel (NOUGHT, COLUMN_COUNT, this);
	model->setHorizontalHeaderItem(COLUMN_1, new QStandardItem(QString(DESCRIPTION_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_2, new QStandardItem(QString(DAY_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_3, new QStandardItem(QString(START_DATE_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_4, new QStandardItem(QString(START_TIME_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_5, new QStandardItem(QString(END_DATE_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_6, new QStandardItem(QString(END_TIME_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_7, new QStandardItem(QString(CAT_HEADER)));
	createMainTable();
	ui.tableView->setModel(model);

	//allows long texts to be wrapped.
	ui.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//set column widths of table.
	ui.tableView->setColumnWidth(COLUMN_1, COLUMN_1_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_1, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_2, COLUMN_2_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_2, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_3, COLUMN_3_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_3, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_4, COLUMN_4_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_4, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_5, COLUMN_5_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_5, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_6, COLUMN_6_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_6, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_7, COLUMN_7_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_7, QHeaderView::Stretch);
	ui.tableView->setMinimumWidth(TOTAL_WIDTH);
	ui.tableView->setMaximumWidth(TOTAL_WIDTH);

	//set up row heights of table.
	ui.tableView->verticalHeader()->setDefaultSectionSize(ROW_HEIGHT);
	
	ui.tableView->setSelectionMode(QAbstractItemView::NoSelection);
}

//=====================================================
//                 CLOCK SET-UP
//=====================================================
void TimeWiseGUI::setupClock() {	
	_clock = new TimeWiseClock();
	ui.label_date->setText(_clock->dateToString());
	ui.label_time->setText(_clock->timeToString());

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT( updateTime() ));
	timer->start();
}

void TimeWiseGUI::updateTime() {
	_clock = new TimeWiseClock();
	ui.label_date->setText(_clock->dateToString());
	ui.label_time->setText(_clock->timeToString());

	if(_logic.getTaskList().checkNewOverdue()){
		_logic.getTaskList().updateOverdueTaskList();
		if(_logic.getScreenToDisplay() == MAIN){
			createMainTable();
		}
	}
}

//=====================================================
//                FONTS SET-UP 
//=====================================================
void TimeWiseGUI::setupFont(){
	QFontDatabase fontDatabase; 
	fontDatabase.addApplicationFont(FONT_CF_JACK_STORY);
	fontDatabase.addApplicationFont(FONT_EHSMB);
	fontDatabase.addApplicationFont(FONT_NEW_CICLE);

	ui.label_date->setFont(QFont(FONT_EHSMB_NAME, DATE_SIZE, BOLD));
	ui.label_time->setFont(QFont(FONT_EHSMB_NAME, TIME_SIZE, BOLD));
}

//=====================================================
//                HOTKEYS SET-UP
//=====================================================
void TimeWiseGUI::setupHotKeys() {
	QShortcut *shortcutUndo = new QShortcut(QKeySequence(HOTKEY_F3), this);
	QShortcut *shortcutRedo = new QShortcut(QKeySequence(HOTKEY_F4), this);
	QShortcut *shortcutMain = new QShortcut(QKeySequence(HOTKEY_F1), this);
	QShortcut *shortcutDone = new QShortcut(QKeySequence(HOTKEY_F2), this);
	QObject::connect(shortcutUndo, SIGNAL(activated()), this, SLOT(undo()));
	QObject::connect(shortcutRedo, SIGNAL(activated()), this, SLOT(redo()));
	QObject::connect(shortcutMain, SIGNAL(activated()), this, SLOT(displayMain()));
	QObject::connect(shortcutDone, SIGNAL(activated()), this, SLOT(displayDone()));
}

//undo slot for undo shortcut
void TimeWiseGUI::undo(){
	std::string messageLog = _logic.processCommand(UNDO_COMMAND);
	QString outputMessage = QString::fromStdString(messageLog);
	ui.label_mlog->setText(outputMessage);
	DISPLAY_TYPE displayType = _logic.getScreenToDisplay();
	displayTaskList(displayType);
}

//redo slot for redo shortcut
void TimeWiseGUI::redo(){
	_logic.processCommand(REDO_COMMAND);
	DISPLAY_TYPE displayType = _logic.getScreenToDisplay();
	displayTaskList(displayType);
}

//displayMain slot for shortcut to display main list
void TimeWiseGUI::displayMain(){
    _logic.processCommand(DISPLAY_MAIN);
	createMainTable();
	ui.label_title->setText(MAIN_TITLE);
}

//displayDone slot for shortcut to display done list
void TimeWiseGUI::displayDone(){
	_logic.processCommand(DISPLAY_DONE);
	vector<Task*> taskList = _logic.getTaskList().getCompletedTaskList();
	createOtherTables(taskList);
	ui.label_title->setText(COMPLETED_TITLE);
}

//=====================================================
//            OVERDUE TASKS COUNT REMINDER
//=====================================================
void TimeWiseGUI::setOverdueMessage(int overdueCount) {
	sprintf_s(buffer, OVERDUE_REMINDER.c_str(), overdueCount);
	QString qOverdue = QString::fromStdString(buffer);
	ui.label_mlog->setText(qOverdue);
}

int TimeWiseGUI::numberOfOverdues() {
	TaskList taskList = _logic.getTaskList();
	std::vector<Task*> overdueTaskList = taskList.getOverdueTaskList();
	int overdueTasksCount = overdueTaskList.size(); 
	return overdueTasksCount;
}

//=====================================================
//                 AUTO-COMPLETER
//=====================================================
void TimeWiseGUI::autoComplete() {
	QStringList descList;
	TaskList taskList = _logic.getTaskList();

	//for search function
	for(int i = 0; i < taskList.undoneSize(); i++) {
		ostringstream outstrDesc;
		outstrDesc << SEARCH_COMMAND << SPACE << taskList.getTask(i)->getDescription();
		QString qDesc = QString::fromStdString(outstrDesc.str());
		descList << qDesc;
	}

	//for display function
	descList << DISPLAY_DONE << DISPLAY_MAIN;

	_descCompleter = new QCompleter(descList, this);
	_descCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	ui.userInput->setCompleter(_descCompleter);
}

//=====================================================
//           KEY-PRESSED EVENTS FOR USER INPUT BOX
//=====================================================
//enables user to press certain keys (up, down, home) while 
//focus is at user input box to do specific tasks.
//Pressing up will retrieve previous line of input.
//Pressing down will retrieve next line of input.
//Pressing home will bring focus away to table.

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
			} else if(keyEvent->key() == Qt::Key_Home) {
				ui.tableView->setFocus();
				return true;
			}
		}
		return false;
	} 
	return QMainWindow::eventFilter(obj, event);
}

void TimeWiseGUI::previous_line() {
	if (lines.empty()) {
		return;
	}

	if (!ui.userInput->text().isEmpty() 
		&& ( current_line >= lines.size() || ui.userInput->text() != lines[current_line])) {
		unfinished = ui.userInput->text();
	}
	if (current_line > NOUGHT) {
		current_line--;
	}
	ui.userInput->setText(lines[current_line]);
	ui.userInput->selectAll();
}

void TimeWiseGUI::next_line() {
	if (lines.empty()) {
		return;
	}

	current_line++;

	if (current_line >= lines.size()) {
		ui.userInput->setText(unfinished);
		unfinished = BLANK;
		current_line = lines.size();
	} else {
		ui.userInput->setText(lines[current_line]);
		ui.userInput->selectAll();
	}
}

//=====================================================
//                HELP PAGE SET-UP
//=====================================================
void TimeWiseGUI::showHelp() {
	_helpScreen = new TimeWiseFeedback();
	_helpScreen->show();
}