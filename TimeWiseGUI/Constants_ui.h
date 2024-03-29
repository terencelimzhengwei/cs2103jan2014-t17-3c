//@author A0097330H
#ifndef CONSTANTS_UI_H
#define CONSTANTS_UI_H

#include <string>

namespace {
	const char* ADD_COMMAND            = "add";
	const char* CLEAR_COMMAND          = "clear";
	const char* DELETE_COMMAND         = "delete";
	const char* DISPLAY_COMMAND        = "display";
	const char* DONE_COMMAND           = "done";
	const char* EDIT_COMMAND           = "edit";
	const char* EXIT_COMMAND           = "exit";
	const char* FILTER_COMMAND         = "filter";
	const char* HELP_COMMAND           = "help";
	const char* SEARCH_COMMAND         = "search";
	const char* UNDONE_COMMAND		   = "undone";
	const char* UNDO_COMMAND           = "undo";
	const char* REDO_COMMAND           = "redo";

	const char* ADD_FORMAT             = "add <description> <start date> <start time> <end date> <end time> <#category>";
	const char* CLEAR_FORMAT           = "clear or clear all / main / completed";
	const char* DELETE_FORMAT          = "delete <ID> / multiple <IDs>";
	const char* DISPLAY_FORMAT         = "display main / done";
	const char* DONE_FORMAT            = "done <IDs> / multiple <IDs>";
	const char* EDIT_FORMAT            = "edit <ID> <contents>";
	const char* FILTER_FORMAT          = "filter <dates> / <#category>";
	const char* SEARCH_FORMAT          = "search <keywords>";
	const char* UNDONE_FORMAT		   = "undone <IDs> / multiple <IDs>";
	const char* DEFAULT_DISPLAY        = "You may: Add, Clear, Delete, Display, Done/Undone, Edit, Filter, Search, Undo/Redo, Help, Exit";
	const std::string OVERDUE_REMINDER = "Reminder! You have %d overdue task(s).";
	const char* EMPTY_INPUT			   = "Please enter a command.";
	const char* CORRUPTED_MESSAGE      = "<font color='red'>Error! Task details may have been lost/altered due to tampering of the text file!</font>";
	const char* OUT_OF_BOUNDS          = "Out of bounds";

	const char* BLANK                  = "";
	const char* SPACE                  = " ";
	const char* MAIN_TITLE             = "Your Tasks";
	const char* COMPLETED_TITLE        = "Completed Tasks";
	const char* SEARCHED_TITLE         = "Searched Tasks";
	const char* FILTERED_TITLE         = "Filtered Tasks";

	const char* OVERDUE_STATUS         = "overdue";
	const char* DONE_STATUS            = "done";

	const char* DISPLAY_MAIN           = "display main";
	const char* DISPLAY_DONE           = "display done";

	const char* CLEAR_ALL			   = "clear all";
	const char* CLEAR_MAIN			   = "clear main";
	const char* CLEAR_COMPLETED		   = "clear completed";

	//Values pertaining to table model configuration
	const int COLUMN_DESCRIPTION        = 0;
	const int COLUMN_DAY		        = 1;
	const int COLUMN_START_DATE		    = 2;
	const int COLUMN_START_TIME         = 3;
	const int COLUMN_END_DATE           = 4;
	const int COLUMN_END_TIME           = 5;
	const int COLUMN_CATEGORY           = 6;
	const int COLUMN_COUNT              = 7;
	const int COLUMN_DESC_WIDTH         = 185;
	const int COLUMN_DAY_WIDTH          = 45;
	const int COLUMN_START_DATE_WIDTH   = 55;
	const int COLUMN_START_TIME_WIDTH   = 48;
	const int COLUMN_END_DATE_WIDTH     = 55;
	const int COLUMN_END_TIME_WIDTH     = 48;
	const int COLUMN_CATEGORY_WIDTH     = 55;
	const int TOTAL_WIDTH               = 535;
	const int ROW_HEIGHT                = 27;

	const char* DESCRIPTION_HEADER = "Description";
	const char* DAY_HEADER         = "Day" ;
	const char* START_DATE_HEADER  = "S. Date";
	const char* START_TIME_HEADER  = "S. Time";
	const char* END_DATE_HEADER    = "E. Date";
	const char* END_TIME_HEADER    = "E. Time";
	const char* CAT_HEADER         = "Category";

	//Strings pertaining to Fonts
	const char* FONT_CF_JACK_STORY = ":/TimeWiseGUI/CFJackStory-Regular.ttf";
	const char* FONT_EHSMB         = ":/TimeWiseGUI/EHSMB.TTF";
	const char* FONT_NEW_CICLE     = ":/TimeWiseGUI/New Cicle Semi.ttf";
	const char* FONT_EHSMB_NAME    = "Electronic Highway Sign";

	//Values Pertaining to Font Sizes and Boldness
	const int DATE_SIZE        = 19;
	const int TIME_SIZE        = 14;
	const int BOLD             = 75;
	const int BOLDEST          = 99;
	const int BOLDED_FONT_SIZE = 9;

	//Hotkey strings
	const char* HOTKEY_F1 = "F1";
	const char* HOTKEY_F2 = "F2";
	const char* HOTKEY_F3 = "F3";
	const char* HOTKEY_F4 = "F4";

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
	const int MAX_LETTERS        = 256;
	char buffer[MAX_LETTERS];
}
#endif