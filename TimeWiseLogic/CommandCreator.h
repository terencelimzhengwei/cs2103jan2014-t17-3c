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
	Command* createCommandAdd(std::string, unsigned int, vector<std::string>);
	Command* createCommandDelete(std::string);
	Command* createCommandEdit(vector<std::string>);
	Command* createCommandClear(std::string);
	Command* createCommandDone(std::string);
	Command* createCommandUndone(std::string);
	Command* createCommandSearch(std::string);
	Command* createCommandFilter(std::string);
	Command* createCommandUndo();
	Command* createCommandRedo();

};

