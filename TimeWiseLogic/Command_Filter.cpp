#include "Command_Filter.h"

Command_Filter::Command_Filter(void){
	_type = FILTER;
	_filterType = CATEGORY;
	_priority = DEFAULTPRI;
	_category = DEFAULT_EMPTY;
	_date = NULL;
}


Command_Filter::~Command_Filter(void){
}

bool Command_Filter::execute(TaskList& tasklist, std::string& feedback){
	*_currentScreen = FILTERED;
	switch(_filterType){
	case CATEGORY: {
		tasklist.populateFilterList(_category);
		int size = tasklist.filteredSize();
		if (size > 0){
			feedback = FILTER_CATEGORY_RESULTS[0] + _category + CATEGORY_STRING;
		} else {
			feedback = FILTER_CATEGORY_RESULTS[1] + _category + CATEGORY_STRING;
		}
		return true;
	}
	case DATE: {
		tasklist.populateFilterList(_date);
		int size = tasklist.filteredSize();
		if (size > 0){
			feedback = FILTER_CATEGORY_RESULTS[2] + _date->toString();
		} else {
			feedback = FILTER_CATEGORY_RESULTS[3] + _date->toString();
		}
		return true;
		
	}
	case PRI:
		tasklist.populateFilterList(_priority);
		feedback = "Tasks displayed have the same level of emergency";
		return true;
	default:
		return false;
	}
	
}

bool Command_Filter::undo(TaskList& tasklist, std::string& feedback){
	*_currentScreen =_previousScreen;
	return true;
}

void Command_Filter::setCategory(std::string category){
	_filterType = CATEGORY;
	_category = category;
}

void Command_Filter::setPriority(PRIORITY priority){
	_filterType = PRI;
	_priority = priority;
}

void Command_Filter::setDate(Date* date){
	_filterType = DATE;
	_date = new Date(*date);
}

void Command_Filter::setPreviousScreen(DISPLAY_TYPE* screen){
	_previousScreen = *screen;
	_currentScreen = screen;
}
 