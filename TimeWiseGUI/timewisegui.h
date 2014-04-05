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
#include <QMessageBox>
#include <QLineEdit>
#include <QKeyEvent>
#include <QRect>
#include <QRegion>
#include <string>
#include <stdexcept>
#include "ui_timewisegui.h"
#include "TimeWiseLogic.h"
#include "timewisefeedback.h"

class TimeWiseGUI : public QMainWindow {
	Q_OBJECT

public:
	TimeWiseGUI(QWidget *parent = 0);
	~TimeWiseGUI();
	QStandardItemModel *model;
	void setupTable();
	void setupClock();
	void setupFont();
	void setupHotKeys();
	
	//These are the functions that sets the data from Logic into the table set up
	void displayTaskList(DISPLAY_TYPE displayType);
	void setMainData();
	void setData(std::vector<Task*>& taskList);

	//These are the functions that pop up a box to inform user of the number of overdue tasks.
	void setOverdueMessage(int overdueCount);
	int numberOfOverdues();

	//These are the functions that allow lineEdit to retrieve previous user actions
	bool eventFilter(QObject* obj, QEvent *event);
	//void wheelEvent(QWheelEvent *);
	void previous_line();
	void next_line();

	//other functions
	void autoComplete();
	//void showFeedback(QString outputMessage);

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
	QCompleter *descCompleter;
	TimeWiseFeedback *feedback;

	//these are for the history retrieval used in line Edit
	int current_line;
	QStringList lines;
	QString unfinished;
};

#endif // TIMEWISEGUI_H
