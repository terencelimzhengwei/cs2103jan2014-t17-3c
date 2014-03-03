#include "Parser.h"

Parser::Parser(void) {
}

Parser::~Parser(void) {
}

Command Parser::interpretCommand(std::string action) {
	std::string commandTypeString = getFirstWord(action);
	std::string description = removeFirstWord(action);

	CMD_TYPE commandType = determineCommandType(commandTypeString);
	Command cmd;
	switch (commandType) {
	case ADD: 
		/* I need to declare a sub class here but i dont know why since we have to return a cmd object
		cmd = new Command_Add();-> gives error
		cmd->setCommandType(); 
		cmd->setDescription(description);
	}*/
		break;
	}
	return cmd;
}

CMD_TYPE Parser::determineCommandType(std::string commandTypeString) {
	convertToLowerCase(commandTypeString);

	if(commandTypeString == "add"){
		return ADD;
	}
	else if(commandTypeString == "delete"){
		return DELETE;
	}
	else if(commandTypeString == "search"){
		return SEARCH;
	}
	else if(commandTypeString == "edit"){
		return EDIT;
	}
	else if(commandTypeString == "display"){
		return DISPLAY;
	}
	else if(commandTypeString == "done"){
		return DONE;
	}
	else if(commandTypeString == "undone"){
		return UNDONE;
	}
	else if(commandTypeString == "undo"){
		return UNDO;
	}
	else if(commandTypeString == "redo"){
		return REDO;
	}
	else if(commandTypeString == "clear"){
		return CLEAR;
	}
	else{
		return UNDEFINED;
	}

}

std::string Parser::getFirstWord(std::string action) {
	unsigned int tStart = 0;
	unsigned int tEnd = 0;

	tEnd = action.find_first_of(" ");

	std::string userCommand = action.substr(tStart, tEnd - tStart);
	return userCommand;
}

string Parser::removeFirstWord(std::string action) {
	unsigned int tStart = 0;
	unsigned int tEnd = 0;

	tStart = action.find_first_of(" ") + 1;
	tEnd = action.size();

	std::string userText = action.substr(tStart, tEnd - tStart);
	return userText;
}

void Parser::convertToLowerCase(std::string &str){

	for(unsigned int i = 0; i < str.length(); i++){
		// convert ONLY the upper case
		if(str[i] >= 'A' && str[i] <= 'Z'){ 
			str[i] += 32;   // convert to small case by adding the number difference as in ASCII 
		}
	}
}

bool Parser::contains(char ch, std::string str){
	if(str.find(ch) == std::string::npos){
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

int Parser::toNum(std::string str){
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
	convertToLowerCase(str);

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

std::string Parser::extractSchedule(std::string &input){
	removeWhiteSpaces(input);
	stack<std::string> words = splitStringBy(' ', input);
	stack<std::string> taskWords;
	stack<std::string> date;
	stack<std::string> time;
	std::string schedule;
	std::string word,originalWord;

	while(!words.empty()){
		word = words.top();
		originalWord = word;
		removeSymbol(word);
		words.pop();

		if( isDateFormat(word) || containsDay(word) ){
			date.push(word);        

			// to throw the preposition word preceeding the date
			if(!words.empty() && isPreposition(words.top()) ){      
				words.pop();
			}
		}
		else if( isTimeFormat(word) ){
			time.push(word);        

			// to throw the preposition word preceeding the date
			if(!words.empty() && isPreposition(words.top())){       
				words.pop();
			}
		}
		else{
			taskWords.push(originalWord);
		}       

	}

	input.clear();
	while(!taskWords.empty()){
		input += taskWords.top();
		input += " ";
		taskWords.pop();
	}
	removeWhiteSpaces(input);

	if(date.empty() && time.empty()){
		schedule = "";
	}
	else if(date.size() == 1 && time.size() == 2){
		schedule = date.top();
		date.pop();
		schedule += " ";
		schedule += time.top();
		time.pop();
		schedule += " - ";
		schedule += time.top();
		time.pop();
	}
	else if(date.size() == 2 && time.size() == 2){
		schedule = date.top();
		date.pop();
		schedule += " ";
		schedule += time.top();
		time.pop();
		schedule += " - ";
		schedule += date.top();
		date.pop();
		schedule += " ";
		schedule += time.top();
		time.pop();
	}
	else if( date.size() == 2 && time.empty()){
		schedule += date.top();
		date.pop();
		schedule += " - ";
		schedule += date.top();
		date.pop();
	}
	else if( time.size() == 2 && date.size() == 0){
		schedule += time.top();
		time.pop();
		schedule += " - "; 
		schedule += time.top();
		time.pop();
	}
	// deadline task or wrong schedule format
	else{ 
		while(!date.empty()){
			schedule += date.top();
			date.pop();
		}
		schedule += " ";
		while(!time.empty()){
			schedule += time.top();
			time.pop();
		}
	}
	removeWhiteSpaces(schedule);

	return schedule;
}

bool Parser::isPreposition(std::string word){
	bool matchFound = false;
	removeSymbol(word);
	for(int i = 0; i < MAX_PREPOSITION; i++){
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

bool Parser::isTimeFormat(std::string time){
	int length = time.size();                                 
	std::string period; 
	std::string beforeDot, afterDot;
	std::string _time;
	bool isTime = false;

	if(length >= 3){
		period = time.substr(length-2, 2); // get the last 2 characters from the string
	}
	else{   
		return isTime;
	}


	if(period == "am" || period == "pm"){
		_time = time.substr(0, time.size()-2); //remove the last two characters which is (am/pm)

		if(contains('.',_time)){
			beforeDot = _time.substr(0, _time.find('.'));
			afterDot = _time.substr(_time.find('.')+1);

			if(beforeDot.size() <= 2 && beforeDot.size() > 0 && afterDot.size() == 2 && isAllNumbers(beforeDot) && isAllNumbers(afterDot)){
				isTime = true;
			}
		}
		else if(isAllNumbers(_time)){
			isTime = true;
		}
	}

	return isTime;

}