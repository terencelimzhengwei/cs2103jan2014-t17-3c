#include "Command_Search.h"


Command_Search::Command_Search(void){
	_type=SEARCH;
	_keyword=DEFAULT_EMPTY;
	_currentScreen=NULL;
}


Command_Search::~Command_Search(void){
}

void Command_Search::setKeyword(std::string keyword){
	_keyword=keyword;
}

bool Command_Search::execute(TaskList& tasklist){
	tasklist.populateSearchList(_keyword,KEYWORD);
	return true;
}

bool Command_Search::undo(TaskList& tasklist){
	*_currentScreen=_previousScreen;
	return true;
}

void Command_Search::setPreviousScreen(DISPLAY_TYPE* screen){
	_previousScreen=*screen;
	_currentScreen=screen;
}
