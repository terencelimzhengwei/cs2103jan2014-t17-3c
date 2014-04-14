//@author A0097330H
#ifndef TIMEWISEGUI_H
#define TIMEWISEGUI_H

#include <iostream>
#include <QCompleter>
#include <QDateTime>
#include <QHeaderView>
#include <QFont>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QLineEdit>
#include <QShortcut>
#include <QStandardItemModel>
#include <QString>
#include <QTimer>
#include <QtWidgets/QMainWindow>
#include <stdio.h>
#include <stdexcept>
#include <string>
#include "ui_timewisegui.h"
#include "Constants_ui.h"
#include "TimeWiseClock.h"
#include "timewisehelp.h"
#include "TimeWiseLogic.h"

class TimeWiseGUI : public QMainWindow {
	Q_OBJECT

public:
	TimeWiseGUI(QWidget *parent = 0);
	~TimeWiseGUI();
	QStandardItemModel *model;
	void configureTable();
	void setupClock();
	void setupFont();
	void setupHotKeys();
	
	//These are the functions that sets the data (main page and other pages separate functions) from Logic into table
	void displayTaskList(DISPLAY_TYPE displayType);
	void createMainTable();
	void setMainData(TaskList& tasklist, vector<int>& latestIndices);
	void highlightMain(TaskList &taskList, int row, int column, vector<int> &boldedIndices);
	void boldMain(vector<int> &boldedIndices, int row, int column); 

	void createOtherTables(std::vector<Task*>& taskList);
	void setOtherData(std::vector<Task*>& otherTaskList, vector<int>& latestIndices);
	void boldOthers(vector<int> &boldedIndices, int row, int column);
	void highlightOthers( std::vector<Task*>& otherTaskList, int row, int column);

	//These are the functions that inform user of the number of overdue tasks.
	void setOverdueMessage();
	int countNumberOfOverdues();

	//These are the functions that allow lineEdit to retrieve previous user actions
	bool eventFilter(QObject* obj, QEvent *event);
	void goToPreviousLine();
	void goToNextLine();

	//other functions
	void autoComplete();
	void checkCorrupted();
	void checkEmpty(QString input);
	void showHelp();

private slots:
	void updateTime();
	void on_userInput_textChanged();
	void on_userInput_returnPressed();
	void undo();
	void redo();
	void displayDone();
	void displayMain();

signals:
    void lineExecuted(QString);

private:
	Ui::TimeWiseGUIClass ui;
	TimeWiseClock *_clock;
	TimeWiseHelp *_helpScreen;
	TimeWiseLogic _logic;
	QCompleter *_autoCompleter;
	
	//these are for the history retrieval used in line Edit
	int current_line;
	QStringList lines;
	QString unfinished;
};
#endif // TIMEWISEGUI_H
