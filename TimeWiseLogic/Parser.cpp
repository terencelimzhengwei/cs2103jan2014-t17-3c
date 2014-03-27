#include "Parser.h"

Parser::Parser(void) {
}

Parser::~Parser(void) {
}

CMD_TYPE Parser::determineCommandType(std::string commandTypeString) {
	commandTypeString = convertToLowerCase(commandTypeString);

	if(commandTypeString == CMD_TYPE_STRING[0]) {
		return ADD;
	}
	else if(commandTypeString == CMD_TYPE_STRING[1]) {
		return DELETE;
	}
	else if(commandTypeString == CMD_TYPE_STRING[2]) {
		return EDIT;
	}
	else if(commandTypeString == CMD_TYPE_STRING[3]) {
		return CLEAR;
	}
	else if(commandTypeString == CMD_TYPE_STRING[4]) {
		return DISPLAY;
	}
	else if(commandTypeString == CMD_TYPE_STRING[5]) {
		return DONE;
	}
	else if(commandTypeString == CMD_TYPE_STRING[6]) {
		return UNDONE;
	}
	else if(commandTypeString == CMD_TYPE_STRING[7]) {
		return UNDO;
	}
	else if(commandTypeString == CMD_TYPE_STRING[8]) {
		return REDO;
	}
	else if(commandTypeString == CMD_TYPE_STRING[9]) {
		return SEARCH;
	} 
	else if(commandTypeString == CMD_TYPE_STRING[10]) {
		return FILTER;
	}
	else {
		return UNDEFINED;
	}
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
	} else if(header == HEADER_STRING[6]) {
		return PRIORITY_HEADER;
	} else {
		return UNDEFINED_HEADER;
	}

}

vector<int> Parser::extractDate(string command, int pos=-1) {
	string monthListLong[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	string monthListShort[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

	bool dateFound = false;

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
						if(dateComponent.size() == 3) {
							output[0] = toNum(dateComponent[2]);
							if(dateComponent[2].length()==2) {
							// !! Need to change the code to get the current century
								output[0] += 2000;
							}
						} else {
							// !! Need to change the code to get the current year
							output[0] = 2014;
						}
				}
			}
			output[3] = 1;
			dateFound = true;
		}
	}

	if(wordReading>=1 && !dateFound) {
		string dateCandidate = convertToLowerCase(parameters[wordReading]);
		for(int i=0;i<12;i++) {
			string monthInNumStr;
			monthInNumStr.push_back(static_cast<char>((i+1)/10+'0'));
			monthInNumStr.push_back(static_cast<char>((i+1)%10+'0'));
			dateCandidate = replaceWord(convertToLowerCase(monthListLong[i]), monthInNumStr, dateCandidate);
			dateCandidate = replaceWord(convertToLowerCase(monthListShort[i]), monthInNumStr, dateCandidate);
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
		string dateCandidate = convertToLowerCase(parameters[wordReading-1]);
		
		for(int i=0;i<12;i++) {
			string monthInNumStr;
			monthInNumStr.push_back(static_cast<char>((i+1)/10+'0'));
			monthInNumStr.push_back(static_cast<char>((i+1)%10+'0'));
			dateCandidate = replaceWord(convertToLowerCase(monthListLong[i]), monthInNumStr, dateCandidate);
			dateCandidate = replaceWord(convertToLowerCase(monthListShort[i]), monthInNumStr, dateCandidate);
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
	
	if(!dateFound) {
		output[3] = 0;
	}
	return output;
}

vector<int> Parser::extractTime(string command, int pos=-1) {
	vector<int> timeArray;
	vector<string> word = splitBySpace(command);
	if(pos==-1) {
		pos = word.size() - 1;
	}
	string wordChecking = word[pos];
	int hour, min;

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
			}
		}
	} else if(wordChecking.length()>=3 && wordChecking.length()<=4 && isAllNumbers(wordChecking)) {
		hour = toNum(wordChecking)/100;
		min = toNum(wordChecking)%100;
		if(hour < 24 && min < 60) {
			timeArray.push_back( hour * 100 + min);
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

std::string Parser::getFirstWord(std::string action) {
	unsigned int tStart = 0;
	unsigned int tEnd = 0;

	tEnd = action.find_first_of(" ");

	std::string userCommand = action.substr(tStart, tEnd - tStart);
	return userCommand;
}

std::string Parser::removeFirstWord(std::string action) {
	std::string first;
	std::istringstream iss(action);
	iss >> first;

	std::ostringstream oss;
	oss << iss.rdbuf();

	return oss.str();
}

std::string Parser::replaceWord(std::string search, std::string replace, std::string subject) {
	int pos;
	do {
		pos = subject.find(search);
		if(pos!=-1) {
			subject.replace(pos, search.length(), replace);
		}
	} while(pos!=-1);
	return subject;
}

string Parser::convertToLowerCase(std::string input) {
	string str = input;

	for(unsigned int i = 0; i < str.length(); i++){
		// convert ONLY the upper case
		if(str[i] >= 'A' && str[i] <= 'Z'){ 
			str[i] += 32;   // convert to small case by adding the number difference as in ASCII 
		}
	}

	return str;
}

bool Parser::isAllNumbers(std::string str){
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

int Parser::toNum(std::string str) {
	//assert(isAllNumbers(str));
	return stoi(str);
}

bool Parser::convertIfNum(const std::string &numInStr, int &num){
	if( isAllNumbers(numInStr) ){
		num = toNum(numInStr);
		return true;
	}
	return false;
}

bool Parser::isDateFormat(std::string str){
	if(extractDate(str)[3]) {
		return true;
	} else {
		return false;
	}
}

bool Parser::containsDay(std::string str){
	bool contains = false;
	str = replaceWord(",","",str);
	str = convertToLowerCase(str);

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

vector<std::string> Parser::splitBySpace(std::string input) {
	vector<string> tokens;
	istringstream iss(input);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
	return tokens;
}

vector<string> Parser::explode(char delimiter, string input) {
	removeWhiteSpaces(input);
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
		removeWhiteSpaces(str);

		if(!str.empty()) {
			splittedStr.push_back(str);
		}
	}
	return splittedStr;
}

stack<std::string> Parser::splitStringBy(char delimiter, std::string input){
	removeWhiteSpaces(input);
	stack<std::string> splittedStr;
	std::string str;
	int pos;

	while(!input.empty()){
		pos = input.find(delimiter);

		if(pos == std::string::npos){
			str = input;
			input.clear();
		}
		else{
			str = input.substr(0, pos);
			input.erase(0, pos+1);
		}
		removeWhiteSpaces(str);

		if(!str.empty()){
			splittedStr.push(str);
		}
	}

	return splittedStr;
}

bool Parser::is24HourTimeFormat(std::string str){
	str = replaceWord(",","",str);

	if( str.size() != 4){
		return false;
	}
	else{
		if(isAllNumbers(str)){
			if(str[0]=='0'||str[0]>'2'){
				return false;
			}else if(str[1]>'3'){
				return false;
			}else if(str[2]>'5'){
				return false;
			}else{
				return true;
			}
		}
		else{
			return false;
		}
	}
}

std::string Parser::getStringAfter(char ch, std::string str){
	int index = str.find(ch);
	string strAfterCh = str.substr(index+1);
	removeWhiteSpaces(strAfterCh);
	return strAfterCh;
}

std::string Parser::getStringBefore(char ch, std::string str){
	int index = str.find(ch);
	std::string strBeforeCh = str.substr(0, index);
	removeWhiteSpaces(strBeforeCh);
	return strBeforeCh;
}


void Parser::removeWhiteSpaces(std::string& str){
	// to remove the preceding white spaces
	while(!str.empty()){
		if(str[0] == ' '){
			str.erase(0,1);
		}
		else{
			break;
		}
	}

	// to remove the trailing white spaces
	while(!str.empty()){
		if(str[str.size()-1] == ' '){
			str.erase(str.size()-1, 1);
		}
		else{
			break;
		}
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

PRIORITY Parser::getPriority(std::string input){
	std::string characterlist;
	characterlist=input.substr(1);
	if(characterlist=="h"||characterlist=="high"){
		return HIGH;
	}else if(characterlist=="m"||characterlist=="medium"){
		return MEDIUM;
	}else if(characterlist=="l"||characterlist=="low"){
		return LOW;
	}else{
		//exceptions
		return LOW;
	}
}

Date* Parser::createDate(string date) {
	int dateInt = toNum(date);
	return new Date(dateInt/1000000, (dateInt/10000)%100, dateInt%10000);
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

bool Parser::isPriority(std::string& input){
	if(input[0]=='!'){
		return true;
	}
	return false;
}


bool Parser::stringExists(string find, string input) {
	if(input.find(find)!=string::npos) {
		return true;
	}
	return false;
}

string Parser::strval(int in) {
	ostringstream os;
	os << in;
	return os.str();
}