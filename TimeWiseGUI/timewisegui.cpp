#include "timewisegui.h"
#include <stdio.h>
#include <QHeaderView>
#include <QShortcut>

//@author A0097330H
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
	int overdues = countNumberOfOverdues();
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
	} else if(ui.userInput->text() == UNDONE_COMMAND) {
		ui.label_help->setText(UNDONE_FORMAT);
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
	vector<int> boldedIndices;
	
	//displays an image if table is empty; else, conceal it.
	if(taskList.undoneSize() == NOUGHT) {
		ui.emptyLogo->show();
	} else {
		ui.emptyLogo->hide();
	}

	setMainData(taskList, boldedIndices);
	
	//scrolls to latest task after all tasks have been set in table.
	if(!boldedIndices.empty()) {
		ui.tableView->scrollTo(model->index(boldedIndices[NOUGHT], NOUGHT));
	}
}

//puts the data in place in the table. Bolds/highlights rows, if necessary
void TimeWiseGUI::setMainData(TaskList& taskList, vector<int>& boldedIndices) {
	boldedIndices = taskList.getBoldIndexList();
	
	//goes through each cell in the table and sets every attributes of every task into the respective cells.
	for(int row = 0; row < taskList.undoneSize(); row++) {
		for(int column = 0; column < COLUMN_COUNT; column++) {
			//add row for every task in taskList dynamically
			model->setRowCount(row + ADJUSTMENT_VALUE);

			QStandardItem* item;
			switch (column) {
			case COLUMN_DESCRIPTION: {
				std::string taskDescription = (taskList.getTask(row))->getDescription();
				QString qTask = QString::fromStdString(taskDescription);
				item = new QStandardItem(qTask);
				break;
			}
			case COLUMN_DAY: {
				std::string taskDay = taskList.getTask(row)->getDayString();
				QString qDay = QString::fromStdString(taskDay);
				item = new QStandardItem(qDay);
				break;
			}
			case COLUMN_START_DATE: {
				if(taskList.getTask(row)->getStartDate()!=NULL){
					std::string taskStartDate = taskList.getTask(row)->getStartDate()->toString();
					QString qStartDate = QString::fromStdString(taskStartDate);
					item = new QStandardItem(qStartDate);
				}
				break;
			}
			case COLUMN_START_TIME: {
				if(taskList.getTask(row)->getStartTime()!=NULL){
					std::string taskStartTime = taskList.getTask(row)->getStartTime()->toString();
					QString qStartTime = QString::fromStdString(taskStartTime);
					item = new QStandardItem(qStartTime);
				}
				break;
			}
			case COLUMN_END_DATE: {
				if(taskList.getTask(row)->getEndDate()!=NULL){
					std::string taskEndDate = taskList.getTask(row)->getEndDate()->toString();
					QString qEndDate = QString::fromStdString(taskEndDate);
					item = new QStandardItem(qEndDate);
				}
				break;
			}
			case COLUMN_END_TIME: {
				if(taskList.getTask(row)->getEndTime()!=NULL){
					std::string taskEndTime = taskList.getTask(row)->getEndTime()->toString();
					QString qEndTime = QString::fromStdString(taskEndTime);
					item = new QStandardItem(qEndTime);
				}
				break;
			}
			case COLUMN_CATEGORY: {
				if(taskList.getTask(row)->getTaskCategory()!= BLANK){
					std::string taskCategory= taskList.getTask(row)->getTaskCategory();
					QString qCategory = QString::fromStdString(taskCategory);
					item = new QStandardItem(qCategory);
				}
				break;
			}
			default: {
				ui.label_mlog->setText(OUT_OF_BOUNDS);	
			}
			}
			model->setItem(row, column, item);

			highlightMain(taskList, row, column, boldedIndices);
			boldMain(boldedIndices, row, column);
		}
	}
}

//highlight description in red if status of that task is overdue, in green is status is done, and in yellow if status is clashed.
void TimeWiseGUI::highlightMain(TaskList &taskList, int row, int column, vector<int> &boldedIndices) {
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
}

//bolds entire task if it is the latest task added/edited. Also bolds existing task(s) that clashes with new task added/edited.
void TimeWiseGUI::boldMain(vector<int> &boldedIndices, int row, int column) {
	QFont font;
	font.setBold(false);
	for(int i = 0; i < boldedIndices.size(); i++) {
		if(row == boldedIndices[i]) {
			font.setWeight(BOLDEST);
			font.setPointSize(BOLDED_FONT_SIZE);
		} 
	}
	model->setData(model->index(row,column), font, Qt::FontRole);
}

//========================================================
//			MANAGES DATA AND SET IT INTO TABLE
//		(OTHER PAGES - Searched, Filtered, Completed)
//========================================================
void TimeWiseGUI::createOtherTables(std::vector<Task*>& otherTaskList) {
	//clears the contents in the table before displaying updated taskList
	model->removeRows(NOUGHT, model->rowCount());
	ui.emptyLogo->hide();
	
	vector<int> boldedIndices;
	setOtherData(otherTaskList, boldedIndices);

	//scrolls to latest task after all tasks have been set in table.
	if(!boldedIndices.empty()) {
		ui.tableView->scrollTo(model->index(boldedIndices[NOUGHT], NOUGHT));
	}
}

void TimeWiseGUI::setOtherData(std::vector<Task*>& otherTaskList, vector<int>& boldedIndices) {
	TaskList taskList = _logic.getTaskList();
	boldedIndices = taskList.getBoldIndexList();

	for(int row = 0; row < otherTaskList.size(); row++) {
		for(int column = 0; column < COLUMN_COUNT; column++) {
			//add row for every task in taskList dynamically
			model->setRowCount(row + ADJUSTMENT_VALUE);

			QStandardItem* item;
			switch (column) {
			case COLUMN_DESCRIPTION: {
				std::string taskDescription = (otherTaskList[row])->getDescription();
				QString qTask = QString::fromStdString(taskDescription);
				item = new QStandardItem(qTask);
				break;
			}
			case COLUMN_DAY: {
				std::string taskDay = otherTaskList[row]->getDayString();
				QString qDay = QString::fromStdString(taskDay);
				item = new QStandardItem(qDay);
				break;
			}
			case COLUMN_START_DATE: {			
				if(otherTaskList[row]->getStartDate()!=NULL){
					std::string taskStartDate = otherTaskList[row]->getStartDate()->toString();
					QString qStartDate = QString::fromStdString(taskStartDate);
					item = new QStandardItem(qStartDate);
				}
				break;
			}
			case COLUMN_START_TIME: {
				if(otherTaskList[row]->getStartTime()!=NULL){
					std::string taskStartTime = otherTaskList[row]->getStartTime()->toString();
					QString qStartTime = QString::fromStdString(taskStartTime);
					item = new QStandardItem(qStartTime);
				}
				break;
			}
			case COLUMN_END_DATE: {
				if(otherTaskList[row]->getEndDate()!=NULL){
					std::string taskEndDate = otherTaskList[row]->getEndDate()->toString();
					QString qEndDate = QString::fromStdString(taskEndDate);
					item = new QStandardItem(qEndDate);
				}
				break;
			}
			case COLUMN_END_TIME: {
				if(otherTaskList[row]->getEndTime()!=NULL){
					std::string taskEndTime = otherTaskList[row]->getEndTime()->toString();
					QString qEndTime = QString::fromStdString(taskEndTime);
					item = new QStandardItem(qEndTime);
				}
				break;
			}
			case COLUMN_CATEGORY: {
				if(otherTaskList[row]->getTaskCategory()!=""){
					std::string taskCategory= otherTaskList[row]->getTaskCategory();
					QString qCategory = QString::fromStdString(taskCategory);
					item = new QStandardItem(qCategory);
				}
				break;
			}
			default: {
				ui.label_mlog->setText(OUT_OF_BOUNDS);	
			}
			}
			model->setItem(row, column, item);

			highlightOthers(otherTaskList, row, column);
			boldOthers(boldedIndices, row, column);
		}
	}
}

//highlight rows in red if status of that task is overdue, in green is status is done, and in yellow if status is clashed.
void TimeWiseGUI::highlightOthers(std::vector<Task*>& otherTaskList, int row, int column) {
	TASK_STATUS taskStatus = otherTaskList[row]->getTaskStatus();
	QString qStatus = QString::fromStdString(TASK_STATUS_STRING[taskStatus]);
	QColor rowColorOverdue(OVERDUE_R_INDEX, OVERDUE_G_INDEX, OVERDUE_B_INDEX, OVERDUE_TRANSPARENCY_INDEX);
	QColor rowColorComplete(COMPLETED_R_INDEX, COMPLETED_G_INDEX, COMPLETED_B_INDEX);
	QColor rowColorClash(CLASH_R_INDEX, CLASH_G_INDEX, CLASH_B_INDEX); 

	//Overdue and Completed status take precedence over Clash status
	//(i.e. if a task is overdue and clashed, highlight it red)
	bool checkClash = otherTaskList[row]->isClash();
	if(qStatus == OVERDUE_STATUS && checkClash) {
		model->setData(model->index(row, column), rowColorOverdue, Qt::BackgroundRole);
	} else if (qStatus == DONE_STATUS && checkClash) {
		model->setData(model->index(row, column), rowColorComplete, Qt::BackgroundRole);
	} else if (checkClash) {
		model->setData(model->index(row, column), rowColorClash, Qt::BackgroundRole);
	} else if (qStatus == OVERDUE_STATUS) {
		model->setData(model->index(row, column), rowColorOverdue, Qt::BackgroundRole);
	} else if (qStatus == DONE_STATUS) {
		model->setData(model->index(row, column), rowColorComplete, Qt::BackgroundRole);
	}
}

//bolds entire task if it is the latest task added/edited. Also bolds existing task(s) that clashes with new task added/edited.
void TimeWiseGUI::boldOthers(vector<int> &boldedIndices, int row, int column) {
	QFont font;
	font.setBold(false);
	for(int i = 0; i < boldedIndices.size(); i++) {
		if(row == boldedIndices[i]) {
			font.setWeight(BOLDEST);
			font.setPointSize(BOLDED_FONT_SIZE);
		} 
	}
	model->setData(model->index(row,column), font, Qt::FontRole);
}

//=====================================================
//             TABLE INITIAL CONFIGURATION
//=====================================================
void TimeWiseGUI::configureTable() {
	//creates model and names column header titles
	model = new QStandardItemModel (NOUGHT, COLUMN_COUNT, this);
	model->setHorizontalHeaderItem(COLUMN_DESCRIPTION, new QStandardItem(QString(DESCRIPTION_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_DAY, new QStandardItem(QString(DAY_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_START_DATE, new QStandardItem(QString(START_DATE_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_START_TIME, new QStandardItem(QString(START_TIME_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_END_DATE, new QStandardItem(QString(END_DATE_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_END_TIME, new QStandardItem(QString(END_TIME_HEADER)));
	model->setHorizontalHeaderItem(COLUMN_CATEGORY, new QStandardItem(QString(CAT_HEADER)));
	createMainTable();
	ui.tableView->setModel(model);

	//set column widths of table.
	ui.tableView->setColumnWidth(COLUMN_DESCRIPTION, COLUMN_DESC_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_DESCRIPTION, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_DAY, COLUMN_DAY_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_DAY, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_START_DATE, COLUMN_START_DATE_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_START_DATE, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_START_TIME, COLUMN_START_TIME_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_START_TIME, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_END_DATE, COLUMN_END_DATE_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_END_DATE, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_END_TIME, COLUMN_END_TIME_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_END_TIME, QHeaderView::Fixed);
	ui.tableView->setColumnWidth(COLUMN_CATEGORY, COLUMN_CATEGORY_WIDTH);
	ui.tableView->horizontalHeader()->setSectionResizeMode(COLUMN_CATEGORY, QHeaderView::Stretch);

	ui.tableView->setMinimumWidth(TOTAL_WIDTH);
	ui.tableView->setMaximumWidth(TOTAL_WIDTH);

	//set up row heights of table.
	ui.tableView->verticalHeader()->setDefaultSectionSize(ROW_HEIGHT);

	//allows long texts to be wrapped.
	ui.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	
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
void TimeWiseGUI::setupFont() {
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
void TimeWiseGUI::undo() {
	std::string messageLog = _logic.processCommand(UNDO_COMMAND);
	QString outputMessage = QString::fromStdString(messageLog);
	ui.label_mlog->setText(outputMessage);

	DISPLAY_TYPE displayType = _logic.getScreenToDisplay();
	displayTaskList(displayType);
}

//redo slot for redo shortcut
void TimeWiseGUI::redo() {
	_logic.processCommand(REDO_COMMAND);

	DISPLAY_TYPE displayType = _logic.getScreenToDisplay();
	displayTaskList(displayType);
}

//displayMain slot for shortcut to display main list
void TimeWiseGUI::displayMain() {
    ui.label_title->setText(MAIN_TITLE);

	_logic.processCommand(DISPLAY_MAIN);
	createMainTable();
}

//displayDone slot for shortcut to display done list
void TimeWiseGUI::displayDone() {
	ui.label_title->setText(COMPLETED_TITLE);
	
	_logic.processCommand(DISPLAY_DONE);
	vector<Task*> taskList = _logic.getTaskList().getCompletedTaskList();
	createOtherTables(taskList);
}

//=====================================================
//            OVERDUE TASKS COUNT REMINDER
//=====================================================
void TimeWiseGUI::setOverdueMessage(int overdueCount) {
	sprintf_s(buffer, OVERDUE_REMINDER.c_str(), overdueCount);
	QString qOverdue = QString::fromStdString(buffer);
	ui.label_mlog->setText(qOverdue);
}

int TimeWiseGUI::countNumberOfOverdues() {
	TaskList taskList = _logic.getTaskList();
	std::vector<Task*> overdueTaskList = taskList.getOverdueTaskList();
	int overdueTasksCount = overdueTaskList.size(); 
	return overdueTasksCount;
}

//=====================================================
//                 AUTO-COMPLETER
//=====================================================
void TimeWiseGUI::autoComplete() {
	QStringList autocompleteList;
	TaskList taskList = _logic.getTaskList();

	//for search function
	for(int i = 0; i < taskList.undoneSize(); i++) {
		ostringstream outstrDesc;
		outstrDesc << SEARCH_COMMAND << SPACE << taskList.getTask(i)->getDescription();
		QString qDesc = QString::fromStdString(outstrDesc.str());
		autocompleteList << qDesc;
	}

	//for display function
	autocompleteList << DISPLAY_DONE << DISPLAY_MAIN;

	//for clear function
	autocompleteList << CLEAR_COMMAND << CLEAR_ALL << CLEAR_MAIN << CLEAR_COMPLETED;

	_autoCompleter = new QCompleter(autocompleteList, this);
	_autoCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	ui.userInput->setCompleter(_autoCompleter);
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
				goToPreviousLine();
				return true;
			} else if(keyEvent->key() == Qt::Key_Down) {
				goToNextLine();
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

void TimeWiseGUI::goToPreviousLine() {
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

void TimeWiseGUI::goToNextLine() {
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
	_helpScreen = new TimeWiseHelp();
	_helpScreen->show();
}

