#include "Parser.h"
//@author A0121023H

Parser::Parser(void) {
}

Parser::~Parser(void) {
}

CMD_TYPE Parser::determineCommandType(string commandTypeString) {
	commandTypeString = strToLower(commandTypeString);

	if(commandTypeString == CMD_TYPE_STRING[ADD]) {
		return ADD;
	}
	else if(commandTypeString == CMD_TYPE_STRING[DELETE]) {
		return DELETE;
	}
	else if(commandTypeString == CMD_TYPE_STRING[EDIT]) {
		return EDIT;
	}
	else if(commandTypeString == CMD_TYPE_STRING[CLEAR]) {
		return CLEAR;
	}
	else if(commandTypeString == CMD_TYPE_STRING[DISPLAY]) {
		return DISPLAY;
	}
	else if(commandTypeString == CMD_TYPE_STRING[DONE]) {
		return DONE;
	}
	else if(commandTypeString == CMD_TYPE_STRING[UNDONE]) {
		return UNDONE;
	}
	else if(commandTypeString == CMD_TYPE_STRING[UNDO]) {
		return UNDO;
	}
	else if(commandTypeString == CMD_TYPE_STRING[REDO]) {
		return REDO;
	}
	else if(commandTypeString == CMD_TYPE_STRING[SEARCH]) {
		return SEARCH;
	} 
	else if(commandTypeString == CMD_TYPE_STRING[FILTER]) {
		return FILTER;
	}
	else {
		return UNDEFINED;
	}
}

TASK_STATUS Parser::getTaskStatus(string input) {
	if(input == TASK_STATUS_STRING[0]){
		return UNCOMPLETED;
	} else if(input == TASK_STATUS_STRING[1])  {
		return COMPLETED;
	} else if(input == TASK_STATUS_STRING[2]) {
		return OVERDUE;
	}
	return UNCOMPLETED;
}

// Check whether a string is a category parameters in a command.
bool Parser::isCategory(string input) {
	for(unsigned int i=0; i<input.length() && i<CATEGORY_SPECIFIER.length(); i++) {
		if(input[i]!=CATEGORY_SPECIFIER[i]) {
			return false;
		}
	}
	return true;
}

// Check whether a word is a preposition, according to the preposition defined in Constants.h
bool Parser::isPreposition(string word) {
	bool matchFound = false;

	// Remove punctuation (e.g. ",", ".") from the words for checking.
	word = removePunctuation(word);

	for(string preposition : PREPOSITION) {
		if(strToLower(word) == strToLower(preposition)) {
			matchFound = true;
			break;
		}
	}
	return matchFound;
}

string Parser::removePunctuation(string input) {
	string output = input;
	for(string punctuation : PUNCTUATION) {
		output = strReplace(punctuation, DEFAULT_EMPTY, input);
	}
	return output;
}

// Date and time related functions

// Create Date object from a dd/mm/yyyy format string.
Date* Parser::createDate(string date) {
	vector<string> dateComponent = explode('/', date);
	if(dateComponent.size() != 3) {
		throw InvalidDateTimeFormatException();
	}

	int day = toInt(dateComponent[0]);
	int month = toInt(dateComponent[1]);
	int year = toInt(dateComponent[2]);

	return new Date(day, month, year);
}

// Create ClockTime object from a hhmm format time.
ClockTime* Parser::createTime(string time) {
	return new ClockTime(toInt(time));
}

// Parse the date and time in user command and move them to Date and ClockTime objects.
void Parser::extractDateTime(string cmd, string& dateTimeRemoved, vector<Date>& dateResult, vector<ClockTime>& timeResult) {
	vector<string> word = splitBySpace(cmd);
	int wordNum = word.size();

	string checkingSentence;
	string checkingSentenceMarkup;
	dateTimeRemoved.clear();

	int concatStartPos;
	int concatEndPos;
	vector<string> checkingResultArray;
	int nonDateTimeWordNum;
	int checkingWordEndingPos;
	Date dateGot;
	ClockTime timeGot;
	int dateCount = 0;
	int timeCount = 0;
	vector<Date> dateArray;
	vector<ClockTime> timeArray;
	string nonDateTimeWord;
	string dateTimeCandidate;

	// Check the existence of date and time starting from the last word in the command
	for(int wordPos=wordNum-1 ; wordPos>=0 ; wordPos--) {
		// Put the last non-checked word into checkingSentence, and try to find the existence of date and time by markupDateTime. 
		if(checkingSentence.empty()) {
			checkingWordEndingPos = wordPos;
			checkingSentence = word[wordPos];
		} else {
			checkingSentence = word[wordPos] + SPACE_PARAMETER + checkingSentence;
		}
		checkingSentenceMarkup = markupDateTime(checkingSentence);
		dateTimeCandidate = getFirstWord(checkingSentenceMarkup);			// If a date/time is marked-up, it will be the first word in the marked-up sentence.
		
		if( dateCount<MAX_DATE_NUM_IN_CMD && isValidConvertedDate(dateTimeCandidate) ||
			timeCount<MAX_TIME_NUM_IN_CMD && isValidConvertedTime(dateTimeCandidate) ) {

			nonDateTimeWordNum = checkingResultArray.size() - 1;				// Once a date/time is marked-up, the remaining words are not date and time.

			// Once a date or time is marked-up, we put the non-date/time part into "dateTimeRemoved".
			concatStartPos = checkingWordEndingPos - nonDateTimeWordNum + 1;	// concatStartPos: the start position of non-date/time part.
			concatEndPos = checkingWordEndingPos;								// concatEndPos:   the end poisiton of non-date/time part.
			nonDateTimeWord = strConcat(word, concatStartPos, concatEndPos);	// get the non-date/time part by strConcat.

			// If a date/time is found before, the last word will be deleted from the non-date/time part if it is a preposition word.
			if( !dateTimeRemoved.empty() && isPreposition(word[concatEndPos]) ) {
				nonDateTimeWord = removeLastWord(nonDateTimeWord);
			}
			dateTimeRemoved = nonDateTimeWord + SPACE_PARAMETER + dateTimeRemoved;
			
			if( isValidConvertedDate(dateTimeCandidate, dateGot) ) {
				dateCount++;
				dateArray.push_back(Date(dateGot));
			} else if( isValidConvertedTime(dateTimeCandidate, timeGot) ) {
				timeCount++;
				timeArray.push_back(ClockTime(timeGot));
			}

			// Clear the checking sentence as the original non-date/time part has been moved to "dateTimeRemoved".
			checkingSentence.clear();
		}
	}
	
	// Move the remaining non-date/time part to "dateTimeRemoved" after all words have been searched.
	if( (dateCount>0 || timeCount>0) && isPreposition(getLastWord(checkingSentence)) ) {
		// If date or time has been found in the command, remove the last word of remaining part if it is a preposition.
		dateTimeRemoved = removeLastWord(checkingSentence) + SPACE_PARAMETER + dateTimeRemoved;
	} else {
		dateTimeRemoved = checkingSentence + SPACE_PARAMETER + dateTimeRemoved;
	}

	dateTimeRemoved = strTruncate(dateTimeRemoved);

	dateResult = dateArray;
	timeResult = timeArray;
}

// Try to mark-up the date from string and check whether it ONLY contains a valid date.
bool Parser::isDate(string input) {
	return isValidConvertedDate(markupDateTime(input));
}

// Try to mark-up the date from string and check whether it ONLY contains a valid date. (with Date object returned)
bool Parser::isDate(string input, Date& outputDate) {
	return isValidConvertedDate(markupDateTime(input), outputDate);
}

// Try to mark-up the timefrom string and check whether it ONLY contains a valid time.
bool Parser::isTime(string input) {
	return isValidConvertedTime(markupDateTime(input));
}

// Try to mark-up the date from string and check whether it ONLY contains a valid date. (with ClockTime object returned)
bool Parser::isTime(string input, ClockTime& outputTime) {
	return isValidConvertedTime(markupDateTime(input), outputTime);
}

// Validate the marked-up date without Date object returned.
bool Parser::isValidConvertedDate(string& input) {
	Date temp;
	return isValidConvertedDate(input, temp);
}

// Validate the marked-up date with Date object returned.
bool Parser::isValidConvertedDate(string& input, Date& outputDate) {
	input = getFirstWord(input);
	input = removePunctuation(input);
	smatch sm;

	string markupDateStart = MARKUP_START + MARKUP_DATE + MARKUP_ATTRB;
	string dateDelim       = MARKUP_DATE_DELIM;
	string markupEnd       = MARKUP_END;

	if(regex_match(input, sm, regex("^" + markupDateStart + "([0-9]{1,2})" + dateDelim + "([0-9]{1,2})" + dateDelim + "([0-9]{4})" + markupEnd + "$"))) {
		try {
			outputDate = Date(toInt(sm[1]), toInt(sm[2]), toInt(sm[3]));
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	}
	return false;
}

// Validate the marked-up time without ClockTime object returned.
bool Parser::isValidConvertedTime(string& input) {
	ClockTime temp;
	return isValidConvertedTime(input, temp);
}

// Validate the marked-up time with ClockTime object returned.
bool Parser::isValidConvertedTime(string& input, ClockTime& outputTime) {

	input = getFirstWord(input);
	input = removePunctuation(input);
	smatch sm;
	
	string markupTimeStart   = MARKUP_START + MARKUP_TIME_24HR + MARKUP_ATTRB;
	string markupTimeAmStart = MARKUP_START + MARKUP_TIME_AM + MARKUP_ATTRB;
	string markupTimePmStart = MARKUP_START + MARKUP_TIME_PM + MARKUP_ATTRB;
	string markupEnd         = MARKUP_END;
	string timeDelim         = MARKUP_TIME_DELIM;

	if(regex_match(input, sm, regex("^" + markupTimeStart + "([0-9]{1,2})" + timeDelim + "([0-9]{2})" + markupEnd + "$"))) {
		try {
			outputTime = ClockTime( toInt(sm[1])*100 + toInt(sm[2]) );
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	} else if(regex_match(input, sm, regex("^" + markupTimeAmStart + "([0-9]{1,2})" + timeDelim + "([0-9]{2})" + markupEnd + "$"))) {
		int hour = toInt(sm[1]);

		if(hour==0 || hour>12) {
			return false;
		}

		try {
			outputTime = ClockTime( (hour%12) * 100 + toInt(sm[2]) );
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	} else if(regex_match(input, sm, regex("^" + markupTimePmStart + "([0-9]{1,2})" + timeDelim + "([0-9]{2})" + markupEnd + "$"))) {
		int hour = toInt(sm[1]);

		if(hour==0 || hour>12) {
			return false;
		}

		try {
			outputTime = ClockTime( (hour%12 + 12) * 100 + toInt(sm[2]) );
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	}
	return false;
}

// Mark-up the possible date and time in the string by using regular expression. 
string Parser::markupDateTime(string cmd) {
	vector<string> weekdayDate(DAY_PER_WEEK);
	Date tempDate;
	int currentYear    = Date::getCurrentYear();
	int currentMonth   = Date::getCurrentMonth();
	int currentDay     = Date::getCurrentDay();
	int currentWeekday = Date::getCurrentWeekday();
	
	string rgx;		// Temporary string variable for storing the regular expression.

	// Ensure the occurance of a space character after each punctuation. 
	cmd = strReplace(",", "," + SPACE_DELIMITER, cmd);
	cmd = strTruncate(cmd);

	// Change the command to lowercases for easier checking.
	cmd = strToLower(cmd);

	string markupMonthStart  = MARKUP_START + MARKUP_MONTH + MARKUP_ATTRB;
	string markupDateStart   = MARKUP_START + MARKUP_DATE + MARKUP_ATTRB;
	string markupTimeStart   = MARKUP_START + MARKUP_TIME_24HR + MARKUP_ATTRB; 
	string markupTimeAmStart = MARKUP_START + MARKUP_TIME_AM + MARKUP_ATTRB; 
	string markupTimePmStart = MARKUP_START + MARKUP_TIME_PM + MARKUP_ATTRB; 
	string markupEnd         = MARKUP_END;
	string dateDelim         = MARKUP_DATE_DELIM;
	string timeDelim         = MARKUP_TIME_DELIM;

	// Converting Date

	// Month-in-word pattern
	// Convert the month in words into <month=X>" where X is the digit(s) of the month.
	for(int i=0 ; i<MONTH_WORD_NUM ; i++) {
		cmd = strIReplace(MONTH_WORD[i], markupMonthStart + strVal(MONTH_WORD_VALUE[i]) + markupEnd, cmd);
	}
	// For month-in-word with year
	rgx = "(^|\\s)" + markupMonthStart + "([1]?[0-9])" + markupEnd + "([0123]?[0-9])(st|nd|rd|th)?,? ([0-9]{2}|[1-9][0-9]{3})($|[\\s,\\.])"; 
	cmd = regex_replace(cmd, regex(rgx), "$1 " + markupDateStart + "$3" + dateDelim + "$2" + dateDelim + "$5" + markupEnd + "$6");
	rgx = "(^|\\s)([0123]?[0-9])(st|nd|rd|th)? ?" + markupMonthStart + "([1]?[0-9])" + markupEnd + ",? ?([0-9]{2}|[1-9][0-9]{3})($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1 " + markupDateStart + "$2" + dateDelim + "$4" + dateDelim + "$5" + markupEnd + "$6");
	// For month-in-word without year
	rgx = "(^|\\s)" + markupMonthStart + "([1]?[0-9])" + markupEnd + " ([0123]?[0-9])(st|nd|rd|th)?($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1 " + markupDateStart + "$3" + dateDelim + "$2" + dateDelim + strVal(currentYear) + markupEnd + "$5");
	rgx = "(^|\\s)([0123]?[0-9])(st|nd|rd|th)? ?" + markupMonthStart + "([0-9])" + markupEnd + "($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1 " + markupDateStart + "$2" + dateDelim + "$4" + dateDelim + strVal(currentYear) + markupEnd + "$5");
	
	// For d--m--yyyy and yyyy--m--d
	cmd = regex_replace(cmd, regex("(^|\\s)([0123]?[0-9])[-\\./]([01]?[0-9])[-\\./]([1-9][0-9]{3})($|[\\s,\\.])"), "$1 " + markupDateStart + "$2" + dateDelim + "$3" + dateDelim + "$4" + markupEnd + "$5");
	cmd = regex_replace(cmd, regex("(^|\\s)([1-9][0-9]{3})[-\\.]([01]?[0-9])[-\\.]([0123]?[0-9])($|[\\s,\\.])"), "$1 " + markupDateStart + "$4" + dateDelim + "$3" + dateDelim + "$2" + markupEnd + "$5");

	// For d--m--yy
	cmd = regex_replace(cmd, regex("(^|\\s)([0-9]{1,2})[-\\./]([01]?[0-9])[-\\./]([0-9]{2})($|[\\s,\\.])"), "$1 " + markupDateStart + "$2" + dateDelim + "$3" + dateDelim + strVal(currentYear/100) + "$4" + markupEnd + "$5");
	
	// For d--m
	cmd = regex_replace(cmd, regex("(^|\\s)([0123]?[0-9])/([01]?[0-9])($|[\\s,\\.])"), "$1 " + markupDateStart + "$2" + dateDelim + "$3" + dateDelim + strVal(currentYear) + markupEnd + "$4");

	// Remove leading 0 in day and month
	cmd = regex_replace(cmd, regex(markupDateStart + "0([0-9])" + dateDelim + "([0-9]{1,2})" + dateDelim + "([0-9]{2}|[0-9]{4})" + markupEnd + "($|[\\s,\\.])"), markupDateStart + "$1" + dateDelim + "$2" + dateDelim + "$3" + markupEnd + "$4");
	cmd = regex_replace(cmd, regex(markupDateStart + "([0-9]{1,2})" + dateDelim + "0([0-9])" + dateDelim + "([0-9]{2}|[0-9]{4})" + markupEnd + "($|[\\s,\\.])"), markupDateStart + "$1" + dateDelim + "$2" + dateDelim + "$3" + markupEnd + "$4");

	// Change the 2-digit year to 4-digit
	cmd = regex_replace(cmd, regex(markupDateStart + "([0-9]{1,2})" + dateDelim + "([0-9]{1,2})" + dateDelim + "([0-9]{2})" + markupEnd + "($|[\\s,\\.])"), markupDateStart + "$1" + dateDelim + "$2" + dateDelim + strVal(currentYear/100) + "$3" + markupEnd + "$4");

	// Change day-in-word (e.g. Today, Tomorrow) into date in digits
	for(int i=0 ; i<DAY_WORD_NUM ; i++) {
		cmd = strIReplace(DAY_WORD[i], markupDateStart + (Date()+DAY_WORD_OFFSET[i]).toFormat() + markupEnd, cmd);
	}

	// Calculate the date of weekdays within coming 7 days
	tempDate.setDateAsToday();
	for(int wd=currentWeekday, i=0 ; i==0 || wd!=((currentWeekday+DAY_PER_WEEK)%DAY_PER_WEEK) ; i++, tempDate++) {
		weekdayDate[wd] = tempDate.toFormat();
		wd = (wd + 1) % DAY_PER_WEEK;
	}

	// Change weekday-in-word into date in digits
	for(int i=0 ; i<WDAY_WORD_NUM ; i++) {
		cmd = strIReplace(WDAY_WORD[i], markupDateStart + weekdayDate[WDAY_WORD_VALUE[i]] + markupEnd, cmd);
	}

	// Converting Time
	
	// Generate a regular expression containing the preposition.
	string regexPreposition;
	for(string preposition : PREPOSITION) {
		regexPreposition = regexPreposition + "|" + preposition;
	}
	regexPreposition.erase(0,1);	// Remove the prceeding '|'.

	// For h:mm
	rgx = "(^|\\s)(" + regexPreposition + ")? ?([0-2]?[0-9])[:\\.]([0-5][0-9])($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1" + markupTimeStart + "$3" + timeDelim + "$4" + markupEnd + "$5");
	// For h am
	rgx = "(^|\\s)(" + regexPreposition + ")? ?([01]?[0-9])[aA]\\.?[mM]\\.?($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1" + markupTimeAmStart + "$3" + timeDelim + "00" + markupEnd + "$4");
	// For h pm
	rgx = "(^|\\s)(" + regexPreposition + ")? ?([01]?[0-9])[pP]\\.?[mM]\\.?($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1" + markupTimePmStart + "$3" + timeDelim + "00" + markupEnd + "$4");
	// For h:mm am
	rgx = "(^|\\s)(" + regexPreposition + ")? ?([01]?[0-9])[:\\.]?([0-5][0-9])[aA]\\.?[mM]\\.?($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1" + markupTimeAmStart + "$3" + timeDelim + "$4" + markupEnd + "$5");
	rgx = "(^|\\s)(" + regexPreposition + ")? ?([01]?[0-9])[:\\.]?([0-5][0-9])[pP]\\.?[mM]\\.?($|[\\s,\\.])";
	// For h:mm pm
	cmd = regex_replace(cmd, regex(rgx), "$1" + markupTimePmStart + "$3" + timeDelim + "$4" + markupEnd + "$5");
	// For hhmm with a date candidate before the time.
	rgx = "(^|\\s)(" + markupDateStart + "[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}" + markupEnd + " )(" + regexPreposition + ")? ?([0-2][0-9])([0-5][0-9])($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1$2" + markupTimeStart + "$3" + timeDelim + "$4" + markupEnd + "$5");
	// For hhmm with a preposition before the time.
	rgx = "(^|\\s)(" + regexPreposition + ") ?([0-2][0-9])([0-5][0-9])($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1" + markupTimeStart + "$3" + timeDelim + "$4" + markupEnd + "$5");
	return strTruncate(cmd);
}

// String processing functions

// Split a string by a 'char' delimiter
vector<string> Parser::explode(char delim, string s) {
	vector<string> result;
    istringstream iss(s);

    for(string token ; std::getline(iss, token, delim) ; ) {
        result.push_back(std::move(token));
    }
    return result;
}

bool Parser::isAllDigit(string str) {
	if(str.empty()) {
		return false;
	}

	for(char c : str) {
		if(c < '0' || c > '9') {
			return false;
		}
	}

	return true;
}

// Concatenate a string vector into a single string
string Parser::strConcat(vector<string> wordArray) {
	if(wordArray.size() == 0) {
		return DEFAULT_EMPTY;
	}

	string output;
	for(string word : wordArray) {
		output = output + SPACE_PARAMETER + word;
	}
	output.erase(0,1);	// Remove the first char which must be a space.
	return output;
}

// Concatenate part of a string vector into a single string
string Parser::strConcat(vector<string> wordArray, unsigned int start, unsigned int end) {
	unsigned int wordNum = wordArray.size();
	if(wordNum==0 || start > end || start >= wordArray.size()) {
		return DEFAULT_EMPTY;
	}
	string output = wordArray[start];
	for(unsigned int pos = start+1 ; pos<=end && pos<=wordNum-1 ; pos++) {
		output = output + SPACE_PARAMETER + wordArray[pos];
	}
	return output;
}

// Case-insensitive string replace.
string Parser::strIReplace(string search, string replace, string subject) {
	int lastPos = 0, pos;
	do {
		pos = strSearch(search, subject, lastPos);
		if(pos!=-1) {
			subject.replace(pos, search.length(), replace);
		}
		lastPos = pos - search.length() + replace.length() + 1;
	} while(pos!=-1);
	return subject;
}

// Convert the whole string into lowercases.
string Parser::strToLower(string input) {
	string str = input;

	for(unsigned int i = 0; i < str.length(); i++) {
		// convert ONLY the upper case
		if(str[i] >= 'A' && str[i] <= 'Z') { 
			str[i] += 32;   // convert to small case by adding the number difference as in ASCII 
		}
	}

	return str;
}

// Case-sensitive string replace.
string Parser::strReplace(string search, string replace, string subject) {
	int lastPos = 0, pos;
	do {
		pos = subject.find(search, lastPos);
		if(pos!=string::npos) {
			subject.replace(pos, search.length(), replace);
		}
		lastPos = pos - search.length() + replace.length() + 1;
	} while(pos!=string::npos);
	return subject;
}

// Case-sensitive string replace with vector<string> input and output.
vector<string> Parser::strReplace(string search, string replace, vector<string> subjectArray) {
	vector<string> outputArray;
	for(string subject : subjectArray) {
		outputArray.push_back(strReplace(search, replace, subject));
	}
	return outputArray;
}

int Parser::strSearch(string keyword, string subject) {
	subject = strToLower(subject);
	keyword = strToLower(keyword);
	return subject.find(keyword);
}

int Parser::strSearch(string keyword, string subject, int pos) {
	subject = strToLower(subject);
	keyword = strToLower(keyword);
	return subject.find(keyword, pos);
}

string Parser::strTruncate(string input) {
	int pos;
	do {
		pos = input.find(SPACE_PARAMETER + SPACE_PARAMETER);
		if(pos!=string::npos) {
			input.replace(pos, 2, SPACE_PARAMETER);
		}
	} while(pos!=string::npos);
	return trim(input);
}

string Parser::strVal(int in) {
	ostringstream os;
	os << in;
	return os.str();
}

vector<string> Parser::strVal(vector<int> inputArray) {
	vector<string> outputArray;
	for(int input : inputArray) {
		outputArray.push_back(strVal(input));
	}
	return outputArray;
}

int Parser::toInt(string str) {
	return stoi(str);
}

string Parser::trim(string str) {
	// Removing the preceding white space
	while(!str.empty() && str[0]==' ') {
		str.erase(0,1);		// Remove the first char in string
	}

	// Removing the trailing white space
	while(!str.empty() && str.back()==' ') {
		str.pop_back();
	}

	return str;
}

string Parser::getFirstWord(string inputString) {
	string firstWord;
	inputString = trim(inputString);
	vector<string> wordArray = splitBySpace(inputString);

	if(wordArray.size()>0) {
		firstWord = wordArray[0];
		firstWord = removePunctuation(firstWord);
	}
	return firstWord;
}

string Parser::removeFirstWord(string inputString) {
	string first;
	istringstream iss(trim(inputString));
	iss >> first;

	std::ostringstream oss;
	oss << iss.rdbuf();

	return oss.str();
}

string Parser::getLastWord(string inputString) {
	string lastWord;
	inputString = trim(inputString);
	vector<string> wordArray = splitBySpace(inputString);

	if(wordArray.size()>0) {
		lastWord = wordArray[wordArray.size()-1];
		lastWord = removePunctuation(lastWord);
	}
	return lastWord;
}

string Parser::removeLastWord(string str) {
	while(str.empty()==false && str.back() == ' ') {
		str.pop_back();
	}
	while(str.empty()==false && str.back() != ' ') {
		str.pop_back();
	}
	while(str.empty()==false && str.back() == ' ') {
		str.pop_back();
	}
	return str;
}

vector<string> Parser::splitBySpace(string input) {
	return explode(' ', input);
}
