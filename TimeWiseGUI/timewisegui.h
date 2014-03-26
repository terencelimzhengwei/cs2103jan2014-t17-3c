#ifndef TIMEWISEGUI_H
#define TIMEWISEGUI_H

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include <QDateTime>
#include <QTimer>
#include <QFontDatabase>
#include <QString>
#include <QCompleter>
#include <QMessageBox>
#include <string>
#include <stdexcept>
#include "ui_timewisegui.h"
#include "TimeWiseLogic.h"

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
	void displayTaskList(DISPLAY_TYPE displayType);
	void setMainData();
	void setData(std::vector<Task*>& taskList);
	int checkEmpty(QString input);
	void autoComplete();
	void setOverdueMessage(int overdueCount);
	int numberOfOverdues();

private slots:
	void updateTime();
	void on_userInput_textChanged();
	void on_userInput_returnPressed();
	void undo();
	void redo();
	void displayDone();
	void displayMain();

private:
	Ui::TimeWiseGUIClass ui;
	TimeWiseLogic _logic;
	QCompleter *descCompleter;
};

#endif // TIMEWISEGUI_H
