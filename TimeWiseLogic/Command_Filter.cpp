#include "Command_Filter.h"

//@author A0097277M
Command_Filter::Command_Filter(void){
	_type = FILTER;
	_filterType = CATEGORY;
	_category = DEFAULT_EMPTY;
	_date = NULL;
}
Command_Filter::~Command_Filter(void){
}

bool Command_Filter::execute(TaskList& tasklist, std::string& feedback){
	*_currentScreen = FILTERED;
	switch(_filterType){
	case CATEGORY:{
		tasklist.populateFilterList(_category);
		int size = tasklist.filteredSize();
		if (size > ZERO){
			feedback = FILTER_CATEGORY_RESULTS[ALL_TASK_CATEGORY] + _category + CATEGORY_STRING;
		} else {
			feedback = FILTER_CATEGORY_RESULTS[NO_TASK_CATEGORY] + _category + CATEGORY_STRING;
		}
		return true;
	}
	case DATE:{
		tasklist.populateFilterList(_date);
		int size = tasklist.filteredSize();
		if (size > ZERO){
			feedback = FILTER_CATEGORY_RESULTS[ALL_TASK_DATE] + _date->toString();
		} else {
			feedback = FILTER_CATEGORY_RESULTS[NO_TASK_CATEGORY] + _date->toString();
		}
		return true;
	}
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

void Command_Filter::setDate(Date* date){
	_filterType = DATE;
	_date = new Date(*date);
}

void Command_Filter::setPreviousScreen(DISPLAY_TYPE* screen){
	_previousScreen = *screen;
	_currentScreen = screen;
}

void Command_Filter::switchScreenTo(DISPLAY_TYPE screen){
	*_currentScreen = screen;
}
 