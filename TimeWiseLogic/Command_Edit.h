#pragma once
#include "command.h"
class Command_Edit :public Command
{
public:
	Command_Edit(void);
	~Command_Edit(void);

	void setIndex(int index);
	void setDescription(std::string desc);
	void setCategory(std::string category);
	void setEndDate(Date* endDate);
	void setStartDate(Date* startDate);
	void setStartTime(ClockTime* startTime);
	void setEndTime(ClockTime* endTime);
	void setDisplayScreen(DISPLAY_TYPE screen);

	bool execute(TaskList& tasklist, std::string& feedback);
	bool undo(TaskList& tasklist);
private:
	int _editIndex;
	std::string _editedDescription;
	std::string _editedCategory;
	Date* _editedEndDate;
	Date* _editedStartDate;
	ClockTime* _editedEndTime;
	ClockTime* _editedStartTime;

	std::string _originalDescription;
	std::string _originalCategory;
	Date* _originalEndDate;
	Date* _originalStartDate;
	ClockTime* _originalEndTime;
	ClockTime* _originalStartTime;

	Task* _editedTask;

	DISPLAY_TYPE _displayScreen;

	bool noDateAndTime();
	bool noDate();
	bool noTime();
	void resetTimeAndDate();
};

