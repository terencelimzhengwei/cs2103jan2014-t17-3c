#pragma once
#include "command.h"
class Command_Search :public Command
{
public:
	Command_Search(void);
	~Command_Search(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
	void setKeyword(std::string keyword);
	void setCategory(std::string category);
	void setTaskStatus(TASK_STATUS status);
	void setPriority(PRIORITY priority);
	void setDate(Date* date);
	void setEmptySlot(Date* date);

private:
	std::string _keyword;
	SEARCH_TYPE _searchType;
	std::string _category;
	TASK_STATUS _status;
	PRIORITY _priority;
	Date* _date;
	Date* _emptySlotDate;

};

