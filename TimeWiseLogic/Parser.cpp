#include "Parser.h"

const string DAY_SHORT_HAND[] = {"yesterday", "ytd", "today", "tomorrow", "tmr"};
const int DAY_SHORT_HAND_OFFSET[] = {-1, -1, 0, 1, 1};

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

vector<int> Parser::extractDate(string command, int pos) {
	Date dateFunction;

	bool dateFound = false;

	command = replaceWord(",", "", command);
	command = replaceWord(".", "", command);

	vector<string> parameters = splitBySpace(command);
	vector<int> output(4);	// output[0] = year, output[1] = month, output[2] = day, output[3] = number of words for date
	if(pos==-1) {
		pos = parameters.size() - 1;
	}

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
							output[0] += dateFunction.getCurrentYear()/100;	
						}
					} else {
						output[0] += dateFunction.getCurrentYear();
					}
				}
				output[3] = 1;
				dateFound = true;
			}
		} else if(dateComponent.size() == 1) {
			int dayShortHandNum = sizeof(DAY_SHORT_HAND_OFFSET) / sizeof(DAY_SHORT_HAND_OFFSET[0]);
			for(int i=0 ; i<dayShortHandNum && !dateFound ; i++) {
				if(strToLower(dateComponent[0]) == strToLower(DAY_SHORT_HAND[i])) {
					dateFunction.setDateAsToday();
					dateFunction += DAY_SHORT_HAND_OFFSET[i];
					output[0] = dateFunction.getYear();
					output[1] = dateFunction.getMonth();
					output[2] = dateFunction.getDay();
					output[3] = 1;
					dateFound = true;
				}
			}
			for(int i=0 ; i<DAY_PER_WEEK && !dateFound; i++) {
				if(strToLower(dateComponent[0])==strToLower(DAY[i]) || strToLower(dateComponent[0])==strToLower(DAY_ABBR[i])) {
					for(dateFunction.setDateAsToday() ; dateFunction.getDayOfTheWeek()!=DAY[i] ; dateFunction++);
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
			dateCandidate = replaceWord(strToLower(MONTH[i]), monthInNumStr, dateCandidate);
			dateCandidate = replaceWord(strToLower(MONTH_ABBR[i]), monthInNumStr, dateCandidate);
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
			dateCandidate = replaceWord(strToLower(MONTH[i]), monthInNumStr, dateCandidate);
			dateCandidate = replaceWord(strToLower(MONTH_ABBR[i]), monthInNumStr, dateCandidate);
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

vector<int> Parser::extractTime(string command, int pos=-1) {
	vector<int> timeArray;
	bool colonExist = false;

	command = replaceWord(",", "", command);
	command = replaceWord(".", "", command);
	vector<string> word = splitBySpace(command);
	if(pos==-1) {
		pos = word.size() - 1;
	}
	string wordChecking = word[pos];
	int hour, min;

	if(wordChecking != replaceWord(":","",wordChecking)) {
		colonExist = true;
	}
	wordChecking = replaceWord(":","",wordChecking);
		
	if(wordChecking.length()>2 && stringExists("am",wordChecking) && wordChecking[wordChecking.length()-1]=='m') {
		wordChecking = replaceWord("am","",wordChecking);
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
		wordChecking = replaceWord("pm","",wordChecking);
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
	if(extractDate(str, explode(' ', str).size()-1)[3]) {
		return true;
	} else {
		return false;
	}
}


bool Parser::isPreposition(std::string word) {
	bool matchFound = false;
	word = replaceWord(",", "", word);
	for(int i = 0; i < MAX_PREPOSITION; i++) {
		if(word == PREPOSITION[i]){
			matchFound = true;
			break;
		}
	}

	return matchFound;
}

bool Parser::isTimeFormat(string time) {
	if(extractTime(time)[1]) {
		return true;
	} else {
		return false;
	}
}

Date* Parser::createDate(std::string date) {
	Date* _date = new Date;
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
	return newDate;
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

vector<string> Parser::explode(char delimiter, string input) {
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

string Parser::replaceWord(string search, string replace, string subject) {
	int pos;
	do {
		pos = subject.find(search);
		if(pos!=-1) {
			subject.replace(pos, search.length(), replace);
		}
	} while(pos!=-1);
	return subject;
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

// Unused function
/*

bool Parser::containsDay(std::string str){
	bool contains = false;
	str = replaceWord(",","",str);
	str = strToLower(str);

	if( str== "today" || str == "tomorrow" ){
		contains = true;
	}
	else{   
		for(int i = 0; i<7; i++){
			if(str == DAY[i]||str==DAY_ABBR[i]){
				contains = true;
				break;
			}
		}
	}

	return contains;
}

HEADER Parser::determineHeaderType(std::string header) {
	if(header == HEADER_STRING[0]) {
		return DESCRIPTION;
	} else if(header == HEADER_STRING[1]) {
		return START_DATE;
	} else if(header == HEADER_STRING[2]) {
		return START_TIME;
	} else if(header == HEADER_STRING[3]) {
		return DUE_DATE;
	} else if(header == HEADER_STRING[4]) {
		return DUE_TIME;
	} else if(header == HEADER_STRING[5]) {
		return CATEGORY_HEADER;
	} else {
		return UNDEFINED_HEADER;
	}

}

*/