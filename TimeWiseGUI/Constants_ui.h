#ifndef CONSTANTS_UI_H
#define CONSTANTS_UI_H

namespace {
	const char* ADD_COMMAND = "add";
	const char* CLEAR_COMMAND = "clear";
	const char* DELETE_COMMAND = "delete";
	const char* DISPLAY_COMMAND = "display";
	const char* DONE_COMMAND = "done";
	const char* EDIT_COMMAND = "edit";
	const char* EXIT_COMMAND = "exit";
	const char* FILTER_COMMAND = "filter";
	const char* HELP_COMMAND = "help";
	const char* SEARCH_COMMAND = "search";
	const char* UNDO_COMMAND = "undo";
	const char* REDO_COMMAND = "redo";

	const char* ADD_FORMAT = "add: <description> <start date> <due date> <start time> <due time> <#category>";
	const char* CLEAR_FORMAT = "clear: all or done or undone";
	const char* DELETE_FORMAT = "delete: <ID>";
	const char* DISPLAY_FORMAT = "display: main or done";
	const char* DONE_FORMAT = "done: <ID>";
	const char* EDIT_FORMAT = "edit: <ID> <contents>";
	const char* FILTER_FORMAT = "filter: <dates> or <#category>";
	const char* SEARCH_FORMAT = "search: <keywords>";
	const char* DEFAULT_DISPLAY = "You may: Add, Clear, Delete, Display, Done, Edit, Filter, Search, Undo, Redo, Help, Exit";

	const char* BLANK = "";
	const char* MAIN_TITLE = "Your Tasks";
	const char* COMPLETED_TITLE = "Completed Tasks";
	const char* SEARCHED_TITLE = "Searched Tasks";
	const char* FILTERED_TITLE = "Filtered Tasks";

	const char* OVERDUE_STATUS = "overdue";
	const char* DONE_STATUS = "done";

	const char* DISPLAY_MAIN = "display main";
	const char* DISPLAY_DONE = "display done";
}

#endif