#pragma once
#include "command.h"
class Command_Filter :public Command
{
public:
	Command_Filter(void);
	~Command_Filter(void);

	bool execute(TaskList& tasklist);
	bool undo(TaskList& tasklist);
	void setKeyword(std::string keyword);
	void setCategory(std::string category);
	void setPriority(PRIORITY priority);
	void setDate(Date* date);

private:
	std::string _keyword;
	SEARCH_TYPE _searchType;
	std::string _category;
	PRIORITY _priority;
	Date* _date;

};

