#pragma once
#include "Command.h"
#include <stack>

//************************************************************
// This class is responsible for deleting an individual task
// specified by its index
//************************************************************
class Command_Delete : public Command{
public:
	Command_Delete(void);
	~Command_Delete(void);
	void addDeletionIndex(int);
	void setDisplayScreen(DISPLAY_TYPE display);

	virtual bool execute(TaskList&, std::string&);
	virtual bool undo(TaskList&, std::string&);
	bool wasUndone();
	bool wasExecuted();
	void lastCmdCalledIs(std::string cmd);
	void permanantlyDeleteTask();
	void redo(TaskList& taskList);
	void deleteTaskWithBackUp(TaskList& taskList);
	void createFeedback(std::string taskFeedback,std::string& feedback);
private:
	std::string _deletionString;
	std::string _lastCmdCalled;
	DISPLAY_TYPE _displayType;
	std::vector<Task*> _deletedTasks;
	std::vector<unsigned int> _deletedTaskIndex;
};

