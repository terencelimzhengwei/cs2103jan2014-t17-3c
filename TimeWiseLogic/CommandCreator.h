#pragma once
#include "Parser.h"
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
#include "Command_Block.h"
#include "Command_Display.h"
#include "Exceptions.h"
#include "Constants.h"
class CommandCreator
{
private:
	std::string _feedbackExceptiontoUI;
	Parser _parser;
public:
	CommandCreator(void);
	~CommandCreator(void);
	std::string getFeedback();
	//flag functions
	bool hasArg(std::string);
	//void hasDescription(std::string);
	bool isValidIndex(int);
	//the below methods are responsible for creating the derived commands

	Command* interpretCommand(std::string userInput,DISPLAY_TYPE& displayType,std::string& commandLineInput, TaskList& tasklist);
	Command* createCommandAdd(std::string parameter, int parameterNum, vector<std::string> parameters,DISPLAY_TYPE* screen);
	Command* createCommandDelete(std::string,DISPLAY_TYPE*);
	Command* createCommandEdit(string command, int parameterNum, vector<string> param, DISPLAY_TYPE* screen);
	Command* createCommandClear(std::string,DISPLAY_TYPE*);
	Command* createCommandDone(std::string,DISPLAY_TYPE*);
	Command* createCommandUndone(std::string,DISPLAY_TYPE*);
	Command* createCommandSearch(std::string,DISPLAY_TYPE*);
	Command* createCommandFilter(std::string,DISPLAY_TYPE*);
	Command* createCommandUndo();
	Command* createCommandRedo();
	Command* createCommandDisplay(string parameter, DISPLAY_TYPE* displayType);
	Command* createCommandBlock(std::string parameter,DISPLAY_TYPE* screen);
};

