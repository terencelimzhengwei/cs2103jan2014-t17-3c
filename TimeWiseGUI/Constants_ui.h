#ifndef CONSTANTS_UI_H
#define CONSTANTS_UI_H

#include <QString>
#include <string>

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
	const std::string OVERDUE_REMINDER = "Reminder! You have %d overdue task(s).";

	const char* BLANK = "";
	const char* SPACE = " ";
	const char* MAIN_TITLE = "Your Tasks";
	const char* COMPLETED_TITLE = "Completed Tasks";
	const char* SEARCHED_TITLE = "Searched Tasks";
	const char* FILTERED_TITLE = "Filtered Tasks";

	const char* OVERDUE_STATUS = "overdue";
	const char* DONE_STATUS = "done";

	const char* DISPLAY_MAIN = "display main";
	const char* DISPLAY_DONE = "display done";

	//Values pertaining to table model
	const int COLUMN_1         = 0;
	const int COLUMN_2		   = 1;
	const int COLUMN_3		   = 2;
	const int COLUMN_4         = 3;
	const int COLUMN_5         = 4;
	const int COLUMN_6         = 5;
	const int COLUMN_7         = 6;
	const int COLUMN_COUNT     = 7;
	const int COLUMN_1_WIDTH   = 190;
	const int COLUMN_2_WIDTH   = 40;
	const int COLUMN_3_WIDTH   = 55;
	const int COLUMN_4_WIDTH   = 48;
	const int COLUMN_5_WIDTH   = 55;
	const int COLUMN_6_WIDTH   = 48;
	const int COLUMN_7_WIDTH   = 55;
	const int TOTAL_WIDTH      = 535;
	const int ROW_HEIGHT       = 27;

	//Strings pertaining to Fonts
	const QString FONT_CF_JACK_STORY = ":/TimeWiseGUI/CFJackStory-Regular.ttf";
	const QString FONT_EHSMB         = ":/TimeWiseGUI/EHSMB.TTF";
	const QString FONT_NEW_CICLE     = ":/TimeWiseGUI/New Cicle Semi.ttf";
	const QString FONT_EHSMB_NAME    = "Electronic Highway Sign";

	//Values Pertaining to Font Sizes and Boldness
	const int DATE_SIZE        = 19;
	const int TIME_SIZE        = 14;
	const int BOLD             = 75;
	const int BOLDEST          = 99;
	const int BOLDED_FONT_SIZE = 9;

	//Hotkey strings
	const QString HOTKEY_F1 = "F1";
	const QString HOTKEY_F2 = "F2";
	const QString HOTKEY_F3 = "F3";
	const QString HOTKEY_F4 = "F4";

	//Colour Indices for highlighting rows
	const int OVERDUE_R_INDEX            = 255;
	const int OVERDUE_G_INDEX            = 0;
    const int OVERDUE_B_INDEX            = 0;
	const int OVERDUE_TRANSPARENCY_INDEX = 50;
	const int COMPLETED_R_INDEX          = 146;
	const int COMPLETED_G_INDEX          = 255;
	const int COMPLETED_B_INDEX          = 192;
	const int CLASH_R_INDEX              = 254;
	const int CLASH_G_INDEX              = 255;
	const int CLASH_B_INDEX              = 185;

	//Miscellaneous
	const int ADJUSTMENT_VALUE   = 1;
	const int NOUGHT             = 0;
	static const int MAX_LETTERS = 256;
	char buffer[MAX_LETTERS];
}

#endif