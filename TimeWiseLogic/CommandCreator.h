#pragma once

//@author A0121023H
#include "Command.h"
#include "Command_Add.h"
#include "Command_Delete.h"
#include "Command_Clear.h"
#include "Command_Done.h"
#include "Command_Undone.h"
#include "Command_Search.h"
#include "Command_Edit.h"
#include "Command_Filter.h"
#include "Command_Undo.h"
#include "Command_Redo.h"
#include "Command_Display.h"
#include "Constants.h"
#include "Exceptions.h"
#include "Parser.h"

//********************************************************************************
// This class is responsible for instantiating command objects once it has
// ascertained the command type (CMD_TYPE) and the validity of the input.
//********************************************************************************
class CommandCreator {
private:
	string _feedbackExceptiontoUI;
public:
	CommandCreator(void);
	~CommandCreator(void);
	string getFeedback();

	//flag functions
	bool hasArg(string);
	bool isValidIndex(int);
	bool isValidRemovalIndex(unsigned int, DISPLAY_TYPE*, TaskList&);

	// Below methods are responsible for creating the derived commands
	Command* interpretCommand(string, DISPLAY_TYPE&, string&, TaskList&);
	Command* createCommandAdd(string, DISPLAY_TYPE*);
	Command* createCommandDelete(vector<string>, DISPLAY_TYPE*, TaskList&);
	Command* createCommandEdit(string, DISPLAY_TYPE*);
	Command* createCommandClear(string, DISPLAY_TYPE*);
	Command* createCommandDone(vector<string>, DISPLAY_TYPE*, TaskList&);
	Command* createCommandUndone(vector<string>, DISPLAY_TYPE* type, TaskList&);
	Command* createCommandSearch(string, DISPLAY_TYPE*);
	Command* createCommandFilter(string, DISPLAY_TYPE*);
	Command* createCommandUndo();
	Command* createCommandRedo();
	Command* createCommandDisplay(string, DISPLAY_TYPE*);

	// Utility methods
	void manipulateInputWithoutCommandWord(CMD_TYPE&, string&);
	CMD_TYPE extractCommandType(string);
	string extractUserInput(string);

};

