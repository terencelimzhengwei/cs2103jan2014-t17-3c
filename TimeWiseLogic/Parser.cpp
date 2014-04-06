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
	else if(commandTypeString == CMD_TYPE_STRING[BLOCK]) {
		return BLOCK;
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

vector<int> Parser::extractDate(string command) {
	return extractDate(command, splitBySpace(command).size() - 1);
}

vector<int> Parser::extractDate(string command, int pos) {
	Date dateFunction;

	bool dateFound = false;

	command = strReplace(",", "", command);
	command = strReplace(".", "", command);

	vector<string> parameters = splitBySpace(command);
	vector<int> output(4);	// output[0] = year, output[1] = month, output[2] = day, output[3] = number of words for date

	int wordReading = pos;

	if(wordReading>=0) {
		vector<string> dateComponent;
		dateComponent = explode('/',parameters[wordReading]);
		if(dateComponent.size() == 2 || dateComponent.size() == 3) {
			if(isAllNumbers(dateComponent[0]) && isAllNumbers(dateComponent[1])) {
				if(dateComponent[0].length()<=2 && dateComponent[1].length()<=2) {
					output[2] = toNum(dateComponent[0]);
					output[1] = toNum(dateComponent[1]);

					dateFunction.setDateAsToday();
					if(dateComponent.size() == 3) {
						output[0] = toNum(dateComponent[2]);
						if(dateComponent[2].length()==2) {
							output[0] += dateFunction.getCurrentYear() - (dateFunction.getCurrentYear()%100);	
						}
					} else {
						output[0] += dateFunction.getCurrentYear();
					}
				}
				output[3] = 1;
				dateFound = true;
			}
		} else if(dateComponent.size() == 1) {
			for(int i=0 ; i<DAY_WORD_NUM && !dateFound ; i++) {
				if(strToLower(dateComponent[0]) == strToLower(DAY_WORD[i])) {
					dateFunction.setDateAsToday();
					dateFunction += DAY_WORD_OFFSET[i];
					output[0] = dateFunction.getYear();
					output[1] = dateFunction.getMonth();
					output[2] = dateFunction.getDay();
					output[3] = 1;
					dateFound = true;
				}
			}
			for(int i=0 ; i<WDAY_WORD_NUM && !dateFound; i++) {
				if(strToLower(dateComponent[0])==strToLower(WDAY_WORD[i])) {
					for(dateFunction.setDateAsToday() ; dateFunction.getWeekDay()!=WDAY_WORD_VALUE[i] ; dateFunction++);
					output[0] = dateFunction.getYear();
					output[1] = dateFunction.getMonth();
					output[2] = dateFunction.getDay();
					output[3] = 1;
					dateFound = true;
				}
			}
		}
	}

	if(wordReading>=1 && !dateFound) {
		string dateCandidate = strToLower(parameters[wordReading]);
		for(int i=0;i<12;i++) {
			string monthInNumStr = strVal(i+1);
			dateCandidate = strReplace(strToLower(MONTH[i]), monthInNumStr, dateCandidate);
			dateCandidate = strReplace(strToLower(MONTH_ABBR[i]), monthInNumStr, dateCandidate);
		}
		if(isAllNumbers(parameters[wordReading-1]) && isAllNumbers(dateCandidate)) {
			dateCandidate = parameters[wordReading-1] + "/" + dateCandidate;
			output = extractDate(dateCandidate,0);
			if(output[0] && output[1] && output[2]) {
				output[3] = 2;
				dateFound = true;
			}
		}
	}
	
	if(wordReading>=2 && !dateFound) {
		string dateCandidate = strToLower(parameters[wordReading-1]);
		
		for(int i=0;i<12;i++) {
			string monthInNumStr = strVal(i+1);
			dateCandidate = strReplace(strToLower(MONTH[i]), monthInNumStr, dateCandidate);
			dateCandidate = strReplace(strToLower(MONTH_ABBR[i]), monthInNumStr, dateCandidate);
		}
		
		if(isAllNumbers(parameters[wordReading-2]) && isAllNumbers(dateCandidate) && isAllNumbers(parameters[wordReading])) {
			dateCandidate = parameters[wordReading-2] + "/" + dateCandidate + "/" + parameters[wordReading];

			output = extractDate(dateCandidate, 0);
			if(output[0] && output[1] && output[2]) {
				output[3] = 3;
				dateFound = true;
			}
		}
	}
	
	if(dateFound) {
		if(output[1]>NUM_OF_MONTHS || output[2]>MAX_DAYS_IN_MONTH[dateFunction.isLeapYear(output[0])][output[1]-1]) {
			output[3] = 0;
			throw InvalidDateTimeFormatException();
		}
	} else {
		output[3] = 0;
	
	}
	return output;
}

// New version of extractDate
pair<Date,Date> Parser::extractDateImproved(string cmd, string& dateRemoved) {
	int currentYear  = Date::getCurrentYear();
	int currentMonth = Date::getCurrentMonth();
	int currentDay   = Date::getCurrentDay();
	
	string rgx;

	// Month-in-word pattern
	for(int m=1 ; m<=12 ; m++) {
		cmd = strIReplace(MONTH[m-1], "-month" + strVal(m), cmd);
		cmd = strIReplace(MONTH_ABBR[m-1], "-month" + strVal(m), cmd);
	}
	// Month-in-word pattern (with year)
	rgx = "(^|\\s|,|.)-month([0-9]{2}) ([0-9]{1,2})(st|nd|rd|th)?,? ([0-9]{2,4})($|\\s|,|.)";
	cmd = regex_replace(cmd, regex(rgx), "$1$3/$2/$5$6");
	rgx = "(^|\\s|,|.)([0-9]{1,2})(st|nd|rd|th)? -month([0-9]{1,2}),? ([0-9]{2,4})($|\\s|,|.)";
	cmd = regex_replace(cmd, regex(rgx), "$1$2/$4/$5$6");
	// Month-in-word pattern (without year)
	rgx = "(^|\\s|,|.)-m([0-9]{1,2}) ([0-9]{1,2})(st|nd|rd|th)?($|\\s|,|.)";
	cmd = regex_replace(cmd, regex(rgx), "$1$3/$2/" + strVal(currentYear) + "$5");
	rgx = "(^|\\s|,|.)([0-9]{1,2})(st|nd|rd|th)? -m([0-9]{1,2})($|\\s|,|.)";
	cmd = regex_replace(cmd, regex(rgx), "$1$2/$4/" + strVal(currentYear) + "$5");

	// 2-2-4 and 4-2-2 pattern
	cmd = regex_replace(cmd, regex("(^|\\s)([0-9]{1,2})[-\\.]([0-9]{1,2})[-\\.]([0-9]{4})($|\\s)"), "$2/$3/$4");
	cmd = regex_replace(cmd, regex("(^|\\s)([0-9]{4})[-\\.]([0-9]{1,2})[-\\.]([0-9]{1,2})($|\\s)"), "$4/$3/$2");

	// 2-2-2 pattern
	cmd = regex_replace(cmd, regex("(^|\\s)([0-9]{1,2})[-\\./]([0-9]{1,2})[-\\./]([0-9]{1,2})($|\\s)"), "$2/$3/" + strVal(currentYear/100) + "$4");
	
	// 2-2 pattern
	cmd = regex_replace(cmd, regex("(^|\\s)([0-9]{1,2})/([0-9]{1,2})($|\\s)"), "$2/$3/" + strVal(currentYear));

	// Remove leading 0 in day and month
	cmd = regex_replace(cmd, regex("(^|\\s)0([0-9])/([0-9]{1,2})/([0-9]{2}|[0-9]{4})($|\\s)"), "$2/$3/$4");
	cmd = regex_replace(cmd, regex("(^|\\s)([0-9]{1,2})/0([0-9])/([0-9]{2}|[0-9]{4})($|\\s)"), "$2/$3/$4");

	return pair<Date,Date>();
}

vector<int> Parser::extractTime(string command, int pos=-1) {
	vector<int> timeArray;
	bool colonExist = false;

	command = strReplace(",", "", command);
	command = strReplace(".", "", command);
	vector<string> word = splitBySpace(command);
	if(pos==-1) {
		pos = word.size() - 1;
	}
	string wordChecking = word[pos];
	int hour, min;

	if(wordChecking != strReplace(":","",wordChecking)) {
		colonExist = true;
	}
	wordChecking = strReplace(":","",wordChecking);
		
	if(wordChecking.length()>2 && stringExists("am",wordChecking) && wordChecking[wordChecking.length()-1]=='m') {
		wordChecking = strReplace("am","",wordChecking);
		if(isAllNumbers(wordChecking) && wordChecking.length()<=4) {
			if(wordChecking.length()<=2) {
				hour = toNum(wordChecking);
				min = 0;
			} else {
				hour = toNum(wordChecking)/100;
				min = toNum(wordChecking)%100;
			}

			if(hour == 12) {
				hour = 0;
			}

			if(hour < 12 && min < 60) {
				timeArray.push_back(hour * 100 + min);
			} else {
				throw InvalidDateTimeFormatException();
			}
		}
	} else if(wordChecking.length()>2 && stringExists("pm",wordChecking) && wordChecking[wordChecking.length()-1]=='m') {
		wordChecking = strReplace("pm","",wordChecking);
		if(isAllNumbers(wordChecking) && wordChecking.length()<=4) {
			if(wordChecking.length()<=2) {
				hour = toNum(wordChecking);
				min = 0;
			} else {
				hour = toNum(wordChecking)/100;
				min = toNum(wordChecking)%100;
			}

			if(hour == 12) {
				hour = 0;
			}

			if(hour < 12 && min < 60) {
				timeArray.push_back((hour+12) * 100 + min);
			} else {
				throw InvalidDateTimeFormatException();
			}
		}
	} else if((colonExist && wordChecking.length()==3 || wordChecking.length()==4) && isAllNumbers(wordChecking)) {
		hour = toNum(wordChecking)/100;
		min = toNum(wordChecking)%100;
		if(hour < 24 && min < 60) {
			timeArray.push_back( hour * 100 + min);
		} else {
			throw InvalidDateTimeFormatException();
		}
	}
	if(timeArray.size()==1) {
		timeArray.push_back(1);
	} else {
		timeArray.push_back(0);
		timeArray.push_back(0);	// Not redundant
	}
	return timeArray;
}

bool Parser::isDateFormat(string str) {
	vector<int> dateData;
	try {
		dateData = extractDate(str, explode(' ', str).size()-1);
	} catch(InvalidDateTimeFormatException&) {
		return false;
	}
	if(dateData[3]!=0) {
		return true;
	} else {
		return false;
	}
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

bool Parser::isTimeFormat(string time) {
	vector<int> timeData;
	try {
		timeData = extractTime(time);
	} catch(InvalidDateTimeFormatException&) {
		return false;
	}
	if(timeData[1]!=0) {
		return true;
	} else {
		return false;
	}
}

Date* Parser::createDate(string date) {
	vector<int> dateData = extractDate(date);
	return new Date(dateData[2], dateData[1], dateData[0]);


	/* Date* _date = new Date;
	std::string dateString = date;
	std::vector<std::string> dateVector;
	std::string temp;
	std::string day="",month="",year="";
	int _day,_month,_year;
	unsigned int index= 0, index1= 0;
	index = dateString.find_first_of("/");
	day = dateString.substr(0,index);
	temp = dateString.substr(index+1);
	if(temp.find_first_of("/")!=std::string::npos){
		index1 = temp.find_first_of("/");
		month = temp.substr(0,index1);
		year = temp.substr(index1+1);
		_year = toNum(year);
	}else{
		month = temp.substr(index+1);
		_year = _date->getCurrentYear();
	}

	_day = toNum(day);
	_month = toNum(month);
	if(_year<100){
		_year=_year + 2000;
	}
	Date* newDate = new Date(_day,_month,_year);
	return newDate;*/
}

ClockTime* Parser::createTime(string time) {
	//return new ClockTime(extractTime(time, 0)[0]);
	return new ClockTime(toNum(time));
}

TASK_STATUS Parser::getTaskStatus(std::string input){
	if(input == TASK_STATUS_STRING[0]){
		return UNCOMPLETED;
	}else if(input == TASK_STATUS_STRING[1]){
		return COMPLETED;
	}else if(input == TASK_STATUS_STRING[2]){
		return OVERDUE;
	}
	return UNCOMPLETED;
}

bool Parser::isCategory(std::string& input){
	if(input[0]=='#'){
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

// Old version of explode(char, string)
/* vector<string> Parser::explode(char delimiter, string input) {
	trim(input);
	vector<string> splittedStr;
	string str;
	int pos;

	while(!input.empty()) {
		pos = input.find(delimiter);
		if(pos == string::npos) {
			str = input;
			input.clear();
		} else {
			str = input.substr(0, pos);
			input.erase(0, pos+1);
		}
		trim(str);

		if(!str.empty()) {
			splittedStr.push_back(str);
		}
	}
	return splittedStr;
}*/
// New version of explode(char, string)
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
	int pos;
	do {
		pos = strSearch(search, subject);
		if(pos!=-1) {
			subject.replace(pos, search.length(), replace);
		}
	} while(pos!=-1);
	return subject;
}

string Parser::strReplace(string search, string replace, string subject) {
	int pos;
	do {
		pos = subject.find(search);
		if(pos!=-1) {
			subject.replace(pos, search.length(), replace);
		}
	} while(pos!=-1);
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

vector<string> Parser::strReplace(vector<string> searchArray, vector<string> replaceArray, vector<string> subjectArray) {
	vector<string> outputArray;
	for(string subject : subjectArray) {
		outputArray.push_back(strReplace(searchArray, replaceArray, subject));
	}
	return outputArray;
}

int Parser::strSearch(string keyword, string subject) {
	subject = strToLower(subject);
	keyword = strToLower(keyword);
	return subject.find(keyword);
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
	vector<string> wordArray = explode(' ', trim(inputString));

	if(wordArray.size()>0) {
		return wordArray[0];
	} else {
		return "";
	}
}

string Parser::removeFirstWord(string inputString) {
	string first;
	istringstream iss(trim(inputString));
	iss >> first;

	std::ostringstream oss;
	oss << iss.rdbuf();

	return oss.str();
}

// Deprecated string functions
// Please use trim(string) instead of removeWhiteSpaces(string&).
void Parser::removeWhiteSpaces(string& str){
	str = trim(str);
}

// Please use explode(char, string); instead of splitBySpace(string).
vector<string> Parser::splitBySpace(string input) {
	vector<string> tokens;
	istringstream iss(input);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
	return tokens;
}
