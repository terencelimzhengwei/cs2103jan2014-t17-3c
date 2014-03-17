#include "Command_Search.h"


Command_Search::Command_Search(void){
	_type=SEARCH;
	_keyword=DEFAULT_EMPTY;
}


Command_Search::~Command_Search(void){
}

void Command_Search::setKeyword(std::string keyword){
	_keyword=keyword;
}

bool Command_Search::execute(TaskList& tasklist){
	tasklist.populateSearchList(_keyword);
	return true;
}

bool Command_Search::undo(TaskList& tasklist){
	return false;
}
