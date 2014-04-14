//@author A0097277M
#include "Command_Search.h"

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
	switchScreenTo(SEARCHED);
	tasklist.populateSearchList(_keyword);
	int size = tasklist.searchedSize();
	if(size > ZERO) {
		feedback = SEARCH_RESULTS[ALL_TASK] + _keyword + CLOSING_BRACKET;
	} else {
		feedback = SEARCH_RESULTS[NO_TASK] + _keyword + CLOSING_BRACKET;
	}
	return true;
}

bool Command_Search::undo(TaskList& tasklist, std::string&){
	switchScreenTo(_previousScreen);
	return true;
}

void Command_Search::setPreviousScreen(DISPLAY_TYPE* screen){
	_previousScreen = *screen;
	_currentScreen = screen;
} 

void Command_Search::switchScreenTo(DISPLAY_TYPE screen){
	*_currentScreen = screen;
}
