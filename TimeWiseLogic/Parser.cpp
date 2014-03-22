#include "Parser.h"

Parser::Parser(void) {
}

Parser::~Parser(void) {
}

CMD_TYPE Parser::determineCommandType(std::string commandTypeString) {
	commandTypeString = convertToLowerCase(commandTypeString);

	if(commandTypeString == "add") {
		return ADD;
	}
	else if(commandTypeString == "delete") {
		return DELETE;
	}
	else if(commandTypeString == "search") {
		return SEARCH;
	}
	else if(commandTypeString == "edit") {
		return EDIT;
	}
	else if(commandTypeString == "display") {
		return DISPLAY;
	}
	else if(commandTypeString == "done") {
		return DONE;
	}
	else if(commandTypeString == "undone") {
		return UNDONE;
	}
	else if(commandTypeString == "undo") {
		return UNDO;
	}
	else if(commandTypeString == "redo") {
		return REDO;
	}
	else if(commandTypeString == "clear") {
		return CLEAR;
	}
	else {
		return UNDEFINED;
	}

}

vector<int> Parser::extractDate(string command, int start, int end) {
	int wordReading = end;
	vector<string> parameters = splitBySpace(removeFirstWord(command));
	vector<string> dateComponent;
	vector<int> output(4);	// output[0] = year, output[1] = month, output[2] = day, output[3] = number of words for date

	if(wordReading>=0) {
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
		} else {
			// Sun, Mon, Tue, Wed, Thur, Fri, Sat
			// Waiting to be completed
		}
	}
	
	if(wordReading>=1) {
		dateComponent.clear();
		dateComponent.push_back(parameters[wordReading-1]);
		dateComponent.push_back(parameters[wordReading]);
	}

	if(wordReading>=2) {
		//dateCandidate[1] = parameters[wordReading-2] + parameters[wordReading+1] + parameters[wordReading];
	}

	return output;
}

std::string Parser::getFirstWord(std::string action) {
	unsigned int tStart = 0;
	unsigned int tEnd = 0;

	tEnd = action.find_first_of(" ");

	std::string userCommand = action.substr(tStart, tEnd - tStart);
	return userCommand;
}

std::string Parser::removeFirstWord(std::string action) {
		unsigned int tStart = 0;
		unsigned int tEnd = 0;
		tStart = action.find_first_of(" ") + 1;
		tEnd = action.size();

		std::string userText = action.substr(tStart, tEnd - tStart);
		return userText;	
}

std::string Parser::replaceWord(std::string search, std::string replace, std::string subject) {
	int pos;
	do {
		pos = subject.find(search);
		if(pos!=-1)	subject.replace(pos, search.length(), replace);
	} while(pos!=-1);
	return subject;
}

string Parser::convertToLowerCase(std::string input){
	string str = input;

	for(unsigned int i = 0; i < str.length(); i++){
		// convert ONLY the upper case
		if(str[i] >= 'A' && str[i] <= 'Z'){ 
			str[i] += 32;   // convert to small case by adding the number difference as in ASCII 
		}
	}

	return str;
}

bool Parser::contains(std::string ch, std::string input)
{
	if(input.find(ch) == std::string::npos){
		return false;
	}
	else{
		return true;
	}
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
	std::vector<int> slashIndex;            // hold the indexes of '/' found in str
	int numOfSlash;                         // total num of '/' found
	std::string     strBfrFirstSlash,       // str before first slash
		strAftFirstSlash,       // str after first slash
		strAftSecondSlash;      // str aft second slash
	bool correctFormat = false;
	removeSymbol(str);

	for(unsigned int i = 0; i < str.size(); i++){
		if( str[i] == '/'){
			slashIndex.push_back(i);
		}
	}
	numOfSlash = slashIndex.size();

	if(numOfSlash == 2){
		strBfrFirstSlash = str.substr(0, slashIndex.at(0));
		strAftFirstSlash = str.substr(slashIndex.at(0)+1, slashIndex.at(1)-(slashIndex.at(0)+1));
		strAftSecondSlash = str.substr(slashIndex.at(1)+1);

		if( (isAllNumbers(strBfrFirstSlash) && strBfrFirstSlash.size() < 3 && !strBfrFirstSlash.empty()) 
			&& (isAllNumbers(strAftFirstSlash) && strAftFirstSlash.size() < 3 && !strAftFirstSlash.empty()) 
			&& (isAllNumbers(strAftSecondSlash) && (strAftSecondSlash.size() == 4 || strAftSecondSlash.size() == 2))){
				correctFormat = true;   // if two slashes and the str before & after first slash is a num with less than 3 digits
				// and the str aft the second slash is a num with not more than 4 and less than 2 digits
		}
	}
	else if(numOfSlash == 1){
		strBfrFirstSlash = str.substr(0, slashIndex.at(0));
		strAftFirstSlash = str.substr(slashIndex.at(0)+1);

		if( (isAllNumbers(strBfrFirstSlash) && strBfrFirstSlash.size() < 3 && !strBfrFirstSlash.empty()) 
			&& (isAllNumbers(strAftFirstSlash) && strAftFirstSlash.size() < 3 && !strAftFirstSlash.empty())){
				correctFormat = true; // the same with the above without checking the str aft second slash
		}
	}
	// else: more than 2 slashes or no slashes present return false

	return correctFormat;
}

bool Parser::containsDay(std::string str){
	bool contains = false;
	removeSymbol(str);
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
	removeSymbol(str);

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
	// to remove the preceeding white spaces
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
	removeSymbol(word);
	for(int i = 0; i < MAX_PREPOSITION; i++) {
		if(word == PREPOSITION[i]){
			matchFound = true;
			break;
		}
	}

	return matchFound;
}

void Parser::removeSymbol(std::string& word){
	// to remove the preceeding symbols
	while(!word.empty()){
		if(word[0] == ','){
			word.erase(0,1);
		}
		else{
			break;
		}
	}

	// to remove the trailing symbols
	while(!word.empty()){
		if(word[word.size()-1] == ','){
			word.erase(word.size()-1, 1);
		}
		else{
			break;
		}
	}
}

bool Parser::isTimeFormat(string time) {
	bool isTime = false;

	time = replaceWord(":", "", time);

	if(time.length()==4 && isAllNumbers(time)) {
		int timeInt = toNum(time);
		if((timeInt%100) < 60 && (timeInt/100 < 24))
			isTime = true;
	}
	
	return isTime;
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

Date* Parser::createDate(std::string date)
{
	Date* _date = new Date;
	std::string dateString=date;
	std::vector<std::string> dateVector;
	std::string temp;
	std::string day="",month="",year="";
	int _day,_month,_year;
	unsigned int index=0, index1=0;
	index=dateString.find_first_of("/");
	day=dateString.substr(0,index);
	temp=dateString.substr(index+1);
	if(temp.find_first_of("/")!=std::string::npos){
		index1=temp.find_first_of("/");
		month=temp.substr(0,index1);
		year=temp.substr(index1+1);
		_year=toNum(year);
	}else{
		month=temp.substr(index+1);
		_year = _date->getCurrentYear();
	}

	_day = toNum(day);
	_month = toNum(month);
	if(_year<100){
		_year=_year+2000;
	}
	Date* newDate = new Date(_day,_month,_year);
	return newDate;
}

ClockTime* Parser::createTime(std::string time)
{
	int timeTemp;
	if(time.size()==4 && isAllNumbers(time)){
		ClockTime* newTime = new ClockTime(toNum(time));
		return newTime;
	}else if(contains("am",time)){
		if(contains(".",time)){
			replaceWord(".","",time);
			timeTemp=toNum(time);
			if(timeTemp>=1200){
				timeTemp=timeTemp-1200;
			}
			ClockTime* newTime = new ClockTime(timeTemp);
			return newTime;
		}else{
			timeTemp=toNum(time);
			if(timeTemp!=12){
				timeTemp*=100;
			}else{
				timeTemp=0;
			}
			ClockTime* newTime = new ClockTime(timeTemp);
			return newTime;
		}
	}else if(contains("pm",time)){
		if(contains(".",time)){
			replaceWord(".","",time);
			timeTemp=toNum(time);
			if(timeTemp<1200){
				timeTemp=timeTemp+1200;
			}
			ClockTime* newTime = new ClockTime(timeTemp);
			return newTime;
		}else{
			timeTemp=toNum(time);
			if(timeTemp!=12){
				timeTemp=(timeTemp*100)+1200;
			}else{
				timeTemp=1200;
			}
			ClockTime* newTime = new ClockTime(timeTemp);
			return newTime;
		}
	}
	return NULL;

}

TASK_STATUS Parser::getTaskStatus(std::string input){
	if(input==TASK_STATUS_STRING[0]){
		return UNCOMPLETED;
	}else if(input==TASK_STATUS_STRING[1]){
		return COMPLETED;
	}else if(input==TASK_STATUS_STRING[2]){
		return OVERDUE;
	}
	return UNCOMPLETED;
}

