#pragma once

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
class CommandCreator{
private:
	std::string _feedbackExceptiontoUI;
public:
	CommandCreator(void);
	~CommandCreator(void);
	std::string getFeedback();
	//flag functions
	bool hasArg(std::string);
	bool isValidIndex(int);
	bool isValidRemovalIndex(unsigned int,DISPLAY_TYPE*,TaskList&);
	//the below methods are responsible for creating the derived commands
	Command* interpretCommand(std::string,DISPLAY_TYPE&,std::string&, TaskList&);
	Command* createCommandAdd(std::string, DISPLAY_TYPE*);
	Command* createCommandDelete(vector<string>,DISPLAY_TYPE*, TaskList&);
	Command* createCommandEdit(string, DISPLAY_TYPE*);
	Command* createCommandClear(std::string,DISPLAY_TYPE*);
	Command* createCommandDone(vector<string>,DISPLAY_TYPE*,TaskList&);
	Command* createCommandUndone(vector<string>,DISPLAY_TYPE* type,TaskList&);
	Command* createCommandSearch(std::string,DISPLAY_TYPE*);
	Command* createCommandFilter(std::string,DISPLAY_TYPE*);
	Command* createCommandUndo();
	Command* createCommandRedo();
	Command* createCommandDisplay(string, DISPLAY_TYPE*);
	//Utility methods
	void manipulateInputWithoutCommandWord(CMD_TYPE&, std::string&);
	CMD_TYPE extractCommandType(std::string);
	std::string extractUserInput(std::string);

};

