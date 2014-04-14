#include "Parser.h"

Parser::Parser(void) {
}

Parser::~Parser(void) {
}

CMD_TYPE Parser::determineCommandType(std::string commandTypeString) {
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

void Parser::extractDateTime(string cmd, string& dateTimeRemoved, vector<Date>& dateResult, vector<ClockTime>& timeResult) {
	string originalCommand = cmd;

	vector<string> word = explode(' ', cmd);
	int wordNum = word.size();

	string checkingSentence = "";
	string checkingResult = "";
	dateTimeRemoved = "";
	vector<string> checkingResultArray;
	int nonDateTimeWordNum;
	int checkingEndWordPos;
	Date dateGot;
	ClockTime timeGot;
	int dateCount = 0;
	int timeCount = 0;
	vector<Date> dateArray;
	vector<ClockTime> timeArray;

	for(int wordPos=wordNum-1 ; wordPos>=0 ; wordPos--) {
		if(checkingSentence.empty()) {
			checkingEndWordPos = wordPos;
			checkingSentence = word[wordPos];
		} else {
			checkingSentence = word[wordPos] + " " + checkingSentence;
		}

		checkingResult = regexDateTime(checkingSentence);

		checkingResultArray = explode(' ', checkingResult);

		if(dateCount<2 && isValidConvertedDate(checkingResultArray[0], dateGot)) {
			dateCount++;
			nonDateTimeWordNum = checkingResultArray.size() - 1;
			for(int i=0 ; i<nonDateTimeWordNum ; i++) {
				if(i || !isPreposition(word[checkingEndWordPos-i])) {
					dateTimeRemoved = word[checkingEndWordPos-i] + " " + dateTimeRemoved;
				}
			}
			checkingSentence.clear();
			dateArray.push_back(Date(dateGot));
		} else if(timeCount<2 && isValidConvertedTime(checkingResultArray[0], timeGot)) {
			timeCount++;
			nonDateTimeWordNum = checkingResultArray.size() - 1;
			for(int i=0 ; i<nonDateTimeWordNum ; i++) {
				if(i || !isPreposition(word[checkingEndWordPos-i])) {
					dateTimeRemoved = word[checkingEndWordPos-i] + " " + dateTimeRemoved;
				}
			}
			checkingSentence.clear();
			timeArray.push_back(ClockTime(timeGot));
		}
	}

	if(dateCount && timeCount && isPreposition(getLastWord(checkingSentence))) {
		dateTimeRemoved = removeLastWord(checkingSentence) + " " + dateTimeRemoved;
	} else {

		dateTimeRemoved = checkingSentence + " " + dateTimeRemoved;
	}
	dateTimeRemoved = strTruncate(dateTimeRemoved);

	dateResult = dateArray;
	timeResult = timeArray;
}

string Parser::regexDateTime(string cmd) {
	vector<string> weekdayDate(7);
	Date tempDate;
	tempDate.setDateAsToday();
	int currentYear    = Date::getCurrentYear();
	int currentMonth   = Date::getCurrentMonth();
	int currentDay     = Date::getCurrentDay();
	int currentWeekday = tempDate.getWeekDay();
	
	string rgx;

	cmd = strReplace(",", ", ", cmd);
	cmd = strTruncate(cmd);

	// Month-in-word pattern
	for(int i=0 ; i<MONTH_WORD_NUM ; i++) {
		cmd = strIReplace(MONTH_WORD[i], "<month=" + strVal(MONTH_WORD_VALUE[i]) + ">", cmd);
	}
	// Month-in-word pattern
	rgx = "(^|\\s)<month=([1]?[0-9])> ([0123]?[0-9])(st|nd|rd|th)?,? ([0-9]{2}|[1-9][0-9]{3})($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1 <date=$3/$2/$5>$6");
	rgx = "(^|\\s)([0123]?[0-9])(st|nd|rd|th)? ?<month=([1]?[0-9])>,? ?([0-9]{2}|[1-9][0-9]{3})($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1 <date=$2/$4/$5>$6");
	// Month-in-word pattern (without year)
	rgx = "(^|\\s)<month=([1]?[0-9])> ([0123]?[0-9])(st|nd|rd|th)?($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1 <date=$3/$2/" + strVal(currentYear) + ">$5");
	rgx = "(^|\\s)([0123]?[0-9])(st|nd|rd|th)? ?<month=([0-9])>($|[\\s,\\.])";
	cmd = regex_replace(cmd, regex(rgx), "$1 <date=$2/$4/" + strVal(currentYear) + ">$5");
	
	// 2-2-4 and 4-2-2 pattern
	cmd = regex_replace(cmd, regex("(^|\\s)([0123]?[0-9])[-\\./]([01]?[0-9])[-\\./]([1-9][0-9]{3})($|[\\s,\\.])"), "$1 <date=$2/$3/$4>$5");
	cmd = regex_replace(cmd, regex("(^|\\s)([1-9][0-9]{3})[-\\.]([01]?[0-9])[-\\.]([0123]?[0-9])($|[\\s,\\.])"), "$1 <date=$4/$3/$2>$5");

	// 2-2-2 pattern
	cmd = regex_replace(cmd, regex("(^|\\s)([0-9]{1,2})[-\\./]([01]?[0-9])[-\\./]([0-9]{2})($|[\\s,\\.])"), "$1 <date=$2/$3/" + strVal(currentYear/100) + "$4>$5");
	
	// 2-2 pattern
	cmd = regex_replace(cmd, regex("(^|\\s)([0123]?[0-9])/([01]?[0-9])($|[\\s,\\.])"), "$1 <date=$2/$3/" + strVal(currentYear) + ">$4");

	// Remove leading 0 in day and month
	cmd = regex_replace(cmd, regex("<date=0([0-9])/([0-9]{1,2})/([0-9]{2}|[0-9]{4})>($|[\\s,\\.])"), "<date=$1/$2/$3>$4");
	cmd = regex_replace(cmd, regex("<date=([0-9]{1,2})/0([0-9])/([0-9]{2}|[0-9]{4})>($|[\\s,\\.])"), "<date=$1/$2/$3>$4");

	// Change the 2-digit year to 4-digit
	cmd = regex_replace(cmd, regex("<date=([0-9]{1,2})/([0-9]{1,2})/([0-9]{2})>($|[\\s,\\.])"), "<date=$1/$2/" + strVal(currentYear/100) + "$3>$4");

	for(int i=0 ; i<DAY_WORD_NUM ; i++) {
		cmd = strIReplace(DAY_WORD[i], "<date=" + (Date()+DAY_WORD_OFFSET[i]).toFormat() + ">", cmd);
	}
	tempDate.setDateAsToday();
	for(int wd=currentWeekday, i=0 ; i==0 || wd!=((currentWeekday+DAY_PER_WEEK)%DAY_PER_WEEK) ; i++, tempDate++) {
		weekdayDate[wd] = tempDate.toFormat();
		wd = (wd + 1) % DAY_PER_WEEK;
	}
	for(int i=0 ; i<WDAY_WORD_NUM ; i++) {
		cmd = strIReplace(WDAY_WORD[i], "<date=" + weekdayDate[WDAY_WORD_VALUE[i]] + ">", cmd);
	}

	// Time stuffs
	cmd = regex_replace(cmd, regex("(^|\\s)(at|from|to)? ?([0-2]?[0-9])[:\\.]([0-5][0-9])($|[\\s,\\.])"), "$1<time=$3:$4>$5");
	cmd = regex_replace(cmd, regex("(^|\\s)(at|from|to)? ?([01]?[0-9])[aA]\\.?[mM]\\.?($|[\\s,\\.])"), "$1<timeAM=$3:00>$4");
	cmd = regex_replace(cmd, regex("(^|\\s)(at|from|to)? ?([01]?[0-9])[pP]\\.?[mM]\\.?($|[\\s,\\.])"), "$1<timePM=$3:00>$4");
	cmd = regex_replace(cmd, regex("(^|\\s)(at|from|to)? ?([01]?[0-9])[:\\.]?([0-5][0-9])[aA]\\.?[mM]\\.?($|[\\s,\\.])"), "$1<timeAM=$3:$4>$5");
	cmd = regex_replace(cmd, regex("(^|\\s)(at|from|to)? ?([01]?[0-9])[:\\.]?([0-5][0-9])[pP]\\.?[mM]\\.?($|[\\s,\\.])"), "$1<timePM=$3:$4>$5");

	cmd = regex_replace(cmd, regex("(^|\\s)(<date=[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}> )(at|from|to)? ?([0-2][0-9])([0-5][0-9])($|[\\s,\\.])"), "$1$2<time=$3:$4>$5");
	cmd = regex_replace(cmd, regex("(^|\\s)([0-2][0-9])([0-5][0-9]) ?(at|from|to)? ?([0-2][0-9])([0-5][0-9])($|[\\s,\\.])"), "$1<time=$2:$3> <time=$5:$6>$7");
	cmd = regex_replace(cmd, regex("(^|\\s)(at|from|to) ?([0-2][0-9])([0-5][0-9])($|[\\s,\\.])"), "$1<time=$3:$4>$5");

	cout << cmd << endl;

	return strTruncate(cmd);
}

// Check whether a word is a preposition, according to the preposition list in Constants.h
bool Parser::isPreposition(string word) {
	bool matchFound = false;
	word = strReplace(",", "", word);
	for(string preposition : PREPOSITION) {
		if(word == preposition) {
			matchFound = true;
			break;
		}
	}
	return matchFound;
}

Date* Parser::createDate(string date) {
	vector<string> dateComponent = explode('/', date);
	if(dateComponent.size() != 3) {
		throw InvalidDateTimeFormatException();
	}

	int day = toNum(dateComponent[0]);
	int month = toNum(dateComponent[1]);
	int year = toNum(dateComponent[2]);

	return new Date(day, month, year);
}

ClockTime* Parser::createTime(string time) {
	return new ClockTime(toNum(time));
}

TASK_STATUS Parser::getTaskStatus(std::string input) {
	if(input == TASK_STATUS_STRING[0]){
		return UNCOMPLETED;
	} else if(input == TASK_STATUS_STRING[1])  {
		return COMPLETED;
	} else if(input == TASK_STATUS_STRING[2]) {
		return OVERDUE;
	}
	return UNCOMPLETED;
}

bool Parser::isCategory(std::string& input) {
	if(input[0]=='#') {
		return true;
	}
	return false;
}

// String functions
string Parser::strToLower(string input) {
	string str = input;

	for(unsigned int i = 0; i < str.length(); i++) {
		// convert ONLY the upper case
		if(str[i] >= 'A' && str[i] <= 'Z'){ 
			str[i] += 32;   // convert to small case by adding the number difference as in ASCII 
		}
	}

	return str;
}

vector<string> Parser::explode(char delim, string s) {
	vector<string> result;
    istringstream iss(s);

    for(string token ; std::getline(iss, token, delim) ; ) {
        result.push_back(std::move(token));
    }
    return result;
}

bool Parser::isAllNumbers(string str) {
	if (str.empty()) {
		return false;
	}

	for(unsigned int i = 0; i < str.size(); i++){
		if( str[i] < '0' || str[i] > '9' ){
			return false;
		}
	}
	return true;
}

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

vector<string> Parser::strReplace(string search, string replace, vector<string> subjectArray) {
	vector<string> outputArray;
	for(string subject : subjectArray) {
		outputArray.push_back(strReplace(search, replace, subject));
	}
	return outputArray;
}

string Parser::strReplace(vector<string> searchArray, string replace, string subject) {
	for(string search : searchArray) {
		subject = strReplace(search, replace, subject);
	}
	return subject;
}

string Parser::strReplace(vector<string> searchArray, vector<string> replaceArray, string subject) {
	for(unsigned int i=0 ; i<searchArray.size() && i<replaceArray.size() ; i++) {
		subject = strReplace(searchArray[i], replaceArray[i], subject);
	}
	return subject;
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
		pos = input.find("  ");
		if(pos!=string::npos) {
			input.replace(pos, 2, " ");
		}
	} while(pos!=string::npos);
	return trim(input);
}

bool Parser::stringExists(string find, string input) {
	if(input.find(find)!=string::npos) {
		return true;
	}
	return false;
}

int Parser::toNum(string str) {
	return stoi(str);
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

string Parser::trim(string str) {
	// Removing the preceding white space
	while(!str.empty()) {
		if(str[0] == ' ') {
			str.erase(0,1);
		} else {
			break;
		}
	}

	// Removing the trailing white space
	while(!str.empty()) {
		if(str[str.length()-1] == ' ') {
			str.erase(str.length()-1, 1);
		} else {
			break;
		}
	}
	return str;
}

// String shortcut functions (Functions make use of written functions)
string Parser::getFirstWord(string inputString) {
	string firstWord;
	vector<string> wordArray = explode(' ', trim(inputString));

	if(wordArray.size()>0) {
		firstWord = wordArray[0];
		firstWord = strReplace(",", "", firstWord);
		firstWord = strReplace(",", "", firstWord);
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
	vector<string> wordArray = explode(' ', trim(inputString));

	if(wordArray.size()>0) {
		lastWord = wordArray[wordArray.size()-1];
		lastWord = strReplace(",", "", lastWord);
		lastWord = strReplace(",", "", lastWord);
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
	vector<string> tokens;
	istringstream iss(input);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
	return tokens;
}

bool Parser::isValidConvertedDate(string& input, Date& outputDate) {
	input = getFirstWord(input);
	input = strReplace(".", "", input);
	input = strReplace(",", "", input);
	smatch sm;
	if(regex_match(input, sm, regex("^<date=([0-9]{1,2})/([0-9]{1,2})/([0-9]{4})>$"))) {
		try {
			outputDate = Date(toNum(sm[1]), toNum(sm[2]), toNum(sm[3]));
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	}
	return false;
}

bool Parser::isValidConvertedTime(string& input, ClockTime& outputTime) {

	input = getFirstWord(input);
	input = strReplace(".", "", input);
	input = strReplace(",", "", input);
	smatch sm;
	if(regex_match(input, sm, regex("^<time=([0-9]{1,2}):([0-9]{2})>$"))) {
		try {
			outputTime = ClockTime( toNum(sm[1])*100 + toNum(sm[2]) );
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	} else if(regex_match(input, sm, regex("^<timeAM=([0-9]{1,2}):([0-9]{2})>$"))) {
		int hour = toNum(sm[1]);

		if(hour==0 || hour>12) {
			return false;
		}

		try {
			outputTime = ClockTime( (hour%12) * 100 + toNum(sm[2]) );
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	} else if(regex_match(input, sm, regex("^<timePM=([0-9]{1,2}):([0-9]{2})>$"))) {
		int hour = toNum(sm[1]);

		if(hour==0 || hour>12) {
			return false;
		}

		try {
			outputTime = ClockTime( (hour%12 + 12) * 100 + toNum(sm[2]) );
		} catch (InvalidDateTimeFormatException e) {
			return false;
		}
		return true;
	}
	return false;
}

bool Parser::isDate(string input) {
	Date temp;
	return isValidConvertedDate(regexDateTime(input), temp);
}

bool Parser::isTime(string input) {
	ClockTime temp;
	return isValidConvertedTime(regexDateTime(input), temp);
}

bool Parser::isDate(string input, Date& outputDate) {
	return isValidConvertedDate(regexDateTime(input), outputDate);
}

bool Parser::isTime(string input, ClockTime& outputTime) {
	return isValidConvertedTime(regexDateTime(input), outputTime);
}