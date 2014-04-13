#ifndef TIMEWISEGUI_H
#define TIMEWISEGUI_H

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include <QDateTime>
#include <QTimer>
#include <QFont>
#include <QFontDatabase>
#include <QString>
#include <QCompleter>
#include <QLineEdit>
#include <QKeyEvent>
#include <string>
#include <iostream>
#include "ui_timewisegui.h"
#include "Constants_ui.h"
#include "TimeWiseClock.h"
#include "TimeWiseLogic.h"
#include "timewisefeedback.h"

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
	
	//These are the functions that sets the data from Logic into table
	void displayTaskList(DISPLAY_TYPE displayType);
	void createMainTable();
	void createOtherTables(std::vector<Task*>& taskList);
	void setMainData(TaskList& tasklist, vector<int>& latestIndices);
	void setOtherData(std::vector<Task*>& otherTaskList, vector<int>& latestIndices);

	//These are the functions that inform user of the number of overdue tasks.
	void setOverdueMessage(int overdueCount);
	int numberOfOverdues();

	//These are the functions that allow lineEdit to retrieve previous user actions
	bool eventFilter(QObject* obj, QEvent *event);
	void previous_line();
	void next_line();

	//other functions
	void autoComplete();
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
	TimeWiseLogic _logic;
	QCompleter *_descCompleter;
	TimeWiseClock *_clock;
	TimeWiseFeedback *_helpScreen;

	//these are for the history retrieval used in line Edit
	int current_line;
	QStringList lines;
	QString unfinished;
};

#endif // TIMEWISEGUI_H
