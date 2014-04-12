#include "Command_Search.h"
//**************************************************************
// This class is responsible for finding tasks which contain the
// keyword specified by the users
//**************************************************************

Command_Search::Command_Search(void){
	_type = SEARCH;
	_keyword = DEFAULT_EMPTY;
	_currentScreen = NULL;
}


Command_Search::~Command_Search(void){
}

void Command_Search::setKeyword(std::string keyword){
	_keyword = keyword;
}

bool Command_Search::execute(TaskList& tasklist, std::string& feedback){
	*_currentScreen = SEARCHED;
	tasklist.populateSearchList(_keyword);
	int size = tasklist.searchedSize();
	if(size > 0) {
		feedback = SEARCH_RESULTS[0] + _keyword + CLOSING_BRACKET;
	} else {
		feedback = SEARCH_RESULTS[1] + _keyword + CLOSING_BRACKET;
	}
	return true;
}

bool Command_Search::undo(TaskList& tasklist, std::string&){
	*_currentScreen = _previousScreen;
	return true;
}

void Command_Search::setPreviousScreen(DISPLAY_TYPE* screen){
	_previousScreen = *screen;
	_currentScreen = screen;
} 

void Command_Search::switchScreenTo(DISPLAY_TYPE screen){
	*_currentScreen = screen;
}
