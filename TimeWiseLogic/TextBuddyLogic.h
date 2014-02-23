#pragma once
#include "TaskList.h"
#include "Storage.h"

//To be done by Terence
class TextBuddyLogic
{
public:
	TextBuddyLogic(void);
	~TextBuddyLogic(void);

private:
	TaskList _taskList;
	Storage _storage;
};

