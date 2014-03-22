#include "Command_Search.h"


Command_Search::Command_Search(void){
	_type=SEARCH;
	_keyword=DEFAULT_EMPTY;
	_searchType=DEFAULT;
	_priority=DEFAULTPRI;
	_category=DEFAULT_EMPTY;
	_date=NULL;
	_emptySlotDate=NULL;
}


Command_Search::~Command_Search(void){
}

void Command_Search::setKeyword(std::string keyword){
	_searchType=KEYWORD;
	_keyword=keyword;
}

bool Command_Search::execute(TaskList& tasklist){
	switch(_searchType){
	case KEYWORD:
		tasklist.populateSearchList(_keyword,KEYWORD);
		return true;
	case CATEGORY:
		tasklist.populateSearchList(_category,CATEGORY);
		return true;
	case DATE:
		tasklist.populateSearchList(_date,DATE);
		return true;
	case STATUS:
		tasklist.populateSearchList(_status);
		return true;
	case PRI:
		tasklist.populateSearchList(_priority);
		return true;
	default:
		return false;
	}
}

bool Command_Search::undo(TaskList& tasklist){
	return false;
}

void Command_Search::setCategory(std::string category){
	_searchType=CATEGORY;

	_category=category;
}

void Command_Search::setTaskStatus(TASK_STATUS status){
	_searchType=STATUS;

	_status=status;
}

void Command_Search::setPriority(PRIORITY priority){
	_searchType=PRI;

	_priority=priority;
}

void Command_Search::setDate(Date* date){
	_searchType=DATE;

	_date=date;
}

void Command_Search::setEmptySlot(Date* date){
	_searchType=EMPTYSLOT;

	_emptySlotDate=date;
}
