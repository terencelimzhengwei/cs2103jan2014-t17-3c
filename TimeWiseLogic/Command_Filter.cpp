#include "Command_Filter.h"

Command_Filter::Command_Filter(void){
	_type=FILTER;
	_filterType=CATEGORY;
	_priority=DEFAULTPRI;
	_category=DEFAULT_EMPTY;
	_date=NULL;
}


Command_Filter::~Command_Filter(void){
}

bool Command_Filter::execute(TaskList& tasklist){
	*_currentScreen=FILTERED;
	switch(_filterType){
	case CATEGORY:
		tasklist.populateFilterList(_category);
		return true;
	case DATE:
		tasklist.populateFilterList(_date);
		return true;
	case PRI:
		tasklist.populateFilterList(_priority);
		return true;
	default:
		return false;
	}
}

bool Command_Filter::undo(TaskList& tasklist){
	*_currentScreen=_previousScreen;
	return true;
}

void Command_Filter::setCategory(std::string category){
	_filterType=CATEGORY;

	_category=category;
}

void Command_Filter::setPriority(PRIORITY priority){
	_filterType=PRI;

	_priority=priority;
}

void Command_Filter::setDate(Date* date){
	_filterType=DATE;

	_date=new Date(*date);
}

void Command_Filter::setPreviousScreen(DISPLAY_TYPE* screen){
	_previousScreen=*screen;
	_currentScreen=screen;
}
