#include "Command_Filter.h"

Command_Filter::Command_Filter(void){
	_type=FILTER;
	_keyword=DEFAULT_EMPTY;
	_searchType=DEFAULT;
	_priority=DEFAULTPRI;
	_category=DEFAULT_EMPTY;
	_date=NULL;
}


Command_Filter::~Command_Filter(void){
}

void Command_Filter::setKeyword(std::string keyword){
	_searchType=KEYWORD;
	_keyword=keyword;
}

bool Command_Filter::execute(TaskList& tasklist){
	switch(_searchType){
	case CATEGORY:
		tasklist.populateFilterList(_category,CATEGORY);
		return true;
	case DATE:
		tasklist.populateFilterList(_date,DATE);
		return true;
	case PRI:
		tasklist.populateFilterList(_priority);
		return true;
	default:
		return false;
	}
}

bool Command_Filter::undo(TaskList& tasklist){
	return false;
}

void Command_Filter::setCategory(std::string category){
	_searchType=CATEGORY;

	_category=category;
}

void Command_Filter::setPriority(PRIORITY priority){
	_searchType=PRI;

	_priority=priority;
}

void Command_Filter::setDate(Date* date){
	_searchType=DATE;

	_date=date;
}