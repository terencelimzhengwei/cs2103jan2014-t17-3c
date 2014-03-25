#pragma once
#include "Parser.h"
#include "Command.h"
#include "Command_Add.h"
#include "Command_Delete.h"
#include "Command_Edit.h"
#include "Command_Clear.h"
#include "Command_Done.h"
#include "Command_Undone.h"
#include "Command_Search.h"
#include "Command_Filter.h"
#include "Command_Undo.h"
#include "Command_Redo.h"
#include "Command_Display.h"
#include "Exceptions.h"
#include "Constants.h"
class CommandCreator
{
private:
	std::vector<string> _feedbackExceptiontoUI;
	Parser _parser;
public:
	CommandCreator(void);
	~CommandCreator(void);
	std::string getFeedback();
	//flag functions
	void flagArg(std::string);
	void flagDescription(std::string);
	void flagIndex(unsigned int);
	//the below methods are responsible for creating the derived commands
	Command* interpretCommand(std::string,DISPLAY_TYPE&);
	Command* createCommandAdd(std::string, unsigned int, vector<std::string>,DISPLAY_TYPE*);
	Command* createCommandDelete(std::string,DISPLAY_TYPE*);
	Command* createCommandEdit(vector<std::string>,DISPLAY_TYPE*);
	Command* createCommandClear(std::string,DISPLAY_TYPE*);
	Command* createCommandDone(std::string,DISPLAY_TYPE*);
	Command* createCommandUndone(std::string,DISPLAY_TYPE*);
	Command* createCommandSearch(std::string,DISPLAY_TYPE*);
	Command* createCommandFilter(std::string,DISPLAY_TYPE*);
	Command* createCommandUndo();
	Command* createCommandRedo();
	Command* createCommandDisplay(string parameter, DISPLAY_TYPE* displayType);
};

