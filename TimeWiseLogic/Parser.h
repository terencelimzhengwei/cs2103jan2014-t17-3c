#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include "Command.h"
#include "Command_Add.h"
#include "Command_Delete.h"
#include "Command_Edit.h"
#include "Constants.h"
#include "Calendar.h"
using namespace std;

//To be done by Antony.

class Parser
{
public:
	Parser(void);
	~Parser(void);
	Command* interpretCommand(std::string action);
	CMD_TYPE determineCommandType(std::string commandTypeString);
	std::string getFirstWord(std::string action);
	std::string removeFirstWord(std::string action);
	std::string replaceWord(std::string search, std::string replace, std::string subject);
	void convertToLowerCase(std::string& str);
	bool contains(char ch, std::string input);
	bool isAllNumbers(std::string);
	int toNum(std::string);
	bool convertIfNum(const std::string &numInStr, int &num);
	bool isDateFormat(std::string);
	bool containsDay(std::string);
	std::vector<std::string> splitBySpace(std::string input);
	std::stack<std::string> splitStringBy(char delimiter, std::string input);
	TASK_TYPE determineTaskType(std::string trimmedInput);
	bool is24HourTimeFormat(std::string);
	std::string getStringAfter(char, std::string);
	std::string getStringBefore(char, std::string);
	void removeWhiteSpaces(std::string&);
	std::string extractSchedule(std::string &input);
	bool isPreposition(std::string);
	void removeSymbol(std::string&);
	bool isTimeFormat(std::string);
};

#endif

//Example for you to reference
/*//@author A0098939B
// this class is the parser class that contains the methods for all the string process method
// required to parse the input given by user
// 
// this class is mainly used by logic component 
// A string will be passed in as parameter to check its meaning, format or even to modify 
// the string
// 
// More details on each method are given in the function declaration below
//
//
#ifndef _STRINGPROCESS_H_
#define _STRINGPROCESS_H_

#include <string>
#include <stack>
#include <assert.h>
#include <vector>
#include "calendar.h"

#define MAX_PREPOSITION 10
using namespace std;

enum COMMAND_TYPE{ADD, DELETE, DISPLAY, FIND, HOME, UPDATE, RESCHEDULE, CHECK, UNCHECK, UNDO, REDO, INVALID, CLEAR};
enum TASK_TYPE{DEADLINE, TIMED, FLOATING};
const char TASK_SPECIFIER = '#';
const char DATE_SEPARATOR = '-';

class StringProcess
{
private:
static const string PREPOSITION[MAX_PREPOSITION]; // the constant array which contain the allowed preposition
public:

// This method will convert the @str to lower case.
// Does not affect any other characters other than symbol
void convertToLowerCase(string &str);

// to get the first word of the string
// if only 1 word is present, return that word
string getFirstWord(string str);

// to remove the first word and return the remaining string
string removeFirstWord(string str);

// this function is will check if the string contain TASK_SPECIFIER and DATE_SEPARATOR
// if both is not present, return TRUE as it is considered as floating task format
// if only ONE TASK_SPECIFIER is present, return TRUE as it is deadline task format
// if BOTH present, check if DATE_SEPARATOR comes before TASK_SPECIFIER
// all other cases will return FALSE to indicate that the add command format is WRONG
//bool correctAddFormat(string input);

// returns true if the string contain the ch
bool contains(char ch, string input);


// to check if the whole string input is just number
// this function is used to identify string of a potential time format or date, month, year 
// However this function does not check if it is a valid time, date, month or year
bool isAllNumbers(string);

// precondition: @string must consist of all number
// this function should be preceeded by isAllNumbers() method
int toNum(string);

bool convertIfNum(const string &numInStr, int &num);

// to check if the string contain '/'
// this function is used to identify string of a potential date format
// returns false if does not contain '/' or contains more than two '/'
// does not check the validity of the date
bool isDateFormat(string);

// this function returns TRUE if the string contain "day" or "tomorrow"
// it is a to identify a string of potential day
// However this function does not check if it is a valid day
// So any string containing the word "day" "tomorrow" will return TRUE
bool containsDay(string);


// this method will return a stack of strings after splitting them according to the delimiter
// if the delimiter is not found in the @string, it will return empty stack
stack<string> splitStringBy(char delimiter, string input);


COMMAND_TYPE determineCommandType(string command);

// this function is to determine the task type
// it determine the task type based on the user input 
//TASK_TYPE determineTaskType(string trimmedInput);

// to check if the string is 24HR time
// it checks the format by checking the length of string which must be 4
// and all 4 characters contain only number
bool is24HourTimeFormat(string);

// to get the string after the specified char
string getStringAfter(char, string);

// to get the string before the specified char
string getStringBefore(char, string);

// this function will remove any preceeding and trailing white spaces in a string
void removeWhiteSpaces(string&);

// this function will analyse a string and extract the schedule (date/day and time)
// out of the string
// After extracting the @input will be = to the task
// while removing the schedule details, it also will remove any preceding 
// preposition word before the date or time.
// If no date or time is present, this function will return an empty string
// 
// Upon extracting, this function will return the schedule in the format required
// by the schedule builder class depending on the type of schedule
//
// For a deadline schedule, the function will return in the following format
//	1) Date 2) Time 3) Date Time
//
// For a timed schedule, the function will return in the following format
// 1) time - time 2) date - date 3) date time - time 4) date time - date time
//
// if more than two date or time present, this function will return the schedule string
// but in an unpredicted format. Since more than two date or time presence will be wrong
// format, this function will return a wrong formatted schedule as well
string extractSchedule(string &input);

// to check if the word is a preposition word as given in the prepostion array
bool isPreposition(string);

// to remove coma or dot preceding and trailling the given string
void removeSymbol(string&);

// the time format should be at least 3 character long contains the suffix am/pm
// at the end of the string
// A decimal may present if minutes is indicated
// Example of correct format are as following:
// 1) 7pm 2) 2.15pm 3) 12.59am 4) 5.05pm
bool isTimeFormat(string);
};

#endif
*/

	/*//@author A0098939B
	#include "stringprocess.h"

	const string StringProcess::PREPOSITION[MAX_PREPOSITION] = {"at", "from", "to", "until", "on", "between", "by", "till", "before"};

	void StringProcess::convertToLowerCase(string &str){

	for(unsigned int i = 0; i < str.length(); i++){
	// convert ONLY the upper case
	if(str[i] >= 'A' && str[i] <= 'Z'){ 
	str[i] += 32;	// convert to small case by adding the number difference as in ASCII 
	}
	}
	}

	string StringProcess::getFirstWord(string str){
	removeWhiteSpaces(str);
	int firstSpaceIndex = str.find(' ');
	string firstWord = str.substr(0, firstSpaceIndex);
	return firstWord;
	}

	string StringProcess::removeFirstWord(string str){
	removeWhiteSpaces(str);
	int firstSpaceIndex = str.find(' ');
	string trimmedStr;

	if(firstSpaceIndex == string::npos){ // if one word
	trimmedStr = "";				//return empty string
	}
	else{
	trimmedStr = str.substr(firstSpaceIndex + 1);
	}
	removeWhiteSpaces(trimmedStr);
	return trimmedStr;
	}

	bool StringProcess::contains(char ch, string str){
	bool contains;

	if(str.find(ch) == string::npos){
	contains = false;
	}
	else{
	contains = true;
	}

	return contains;
	}


	bool StringProcess::isAllNumbers(string str){
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

	int StringProcess::toNum(string str){
	assert(isAllNumbers(str));
	return stoi(str);
	}

	bool StringProcess::convertIfNum(const string &numInStr, int &num){
	bool result = false;

	if( isAllNumbers(numInStr) ){
	num = toNum(numInStr);
	result = true;
	}
	return result;
	}

	bool StringProcess::isDateFormat(string str){
	vector<int> slashIndex;		// hold the indexes of '/' found in str
	int numOfSlash;				// total num of '/' found
	string	strBfrFirstSlash,	// str before first slash
	strAftFirstSlash,	// str after first slash
	strAftSecondSlash;	// str aft second slash
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
	correctFormat = true;	// if two slashes and the str before & after first slash is a num with less than 3 digits
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

	bool StringProcess::containsDay(string str){
	bool contains = false;
	removeSymbol(str);
	convertToLowerCase(str);

	if( str== "today" || str == "tomorrow" ){
	contains = true;
	}
	else{	
	for(int i = 0; i<7; i++){
	if(str == DAY[i]){
	contains = true;
	break;
	}
	}
	}

	return contains;
	}

	stack<string> StringProcess::splitStringBy(char delimiter, string input){
	removeWhiteSpaces(input);
	stack<string> splittedStr;
	string str;
	int pos;

	while(!input.empty()){
	pos = input.find(delimiter);

	if(pos == string::npos){
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

	COMMAND_TYPE StringProcess::determineCommandType(string command){
	convertToLowerCase(command);

	if(command == "add"){
	return ADD;
	}
	else if(command == "delete"){
	return DELETE;
	}
	else if(command == "find"){
	return FIND;
	}
	else if(command == "update"){
	return UPDATE;
	}
	else if(command == "display"){
	return DISPLAY;
	}
	else if(command == "home"){
	return HOME;
	}
	else if(command == "reschedule"){
	return RESCHEDULE;
	}
	else if(command == "done"){
	return CHECK;
	}
	else if(command == "undone"){
	return UNCHECK;
	}
	else if(command == "undo"){
	return UNDO;
	}
	else if(command == "redo"){
	return REDO;
	}
	else if(command == "clear"){
	return CLEAR;
	}
	else if(command == "home"){
	return HOME;
	}
	else{
	return INVALID;
	}

	}

	bool StringProcess::is24HourTimeFormat(string str){
	bool correctFormat;
	removeSymbol(str);

	if( str.size() != 4){
	correctFormat = false;
	}
	else{
	if(isAllNumbers(str)){
	correctFormat = true;
	}
	else{
	correctFormat = false;
	}
	}

	return correctFormat;
	}

	string StringProcess::getStringAfter(char ch, string str){
	int index = str.find(ch);
	string strAfterCh = str.substr(index+1);
	removeWhiteSpaces(strAfterCh);
	return strAfterCh;
	}

	string StringProcess::getStringBefore(char ch, string str){
	int index = str.find(ch);
	string strBeforeCh = str.substr(0, index);
	removeWhiteSpaces(strBeforeCh);
	return strBeforeCh;
	}


	void StringProcess::removeWhiteSpaces(string& str){
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

	string StringProcess::extractSchedule(string &input){
	removeWhiteSpaces(input);
	stack<string> words = splitStringBy(' ', input);
	stack<string> taskWords;
	stack<string> date;
	stack<string> time;
	string schedule;
	string word,originalWord;

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

	bool StringProcess::isPreposition(string word){
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

	void StringProcess::removeSymbol(string& word){
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

	bool StringProcess::isTimeFormat(string time){
	int length = time.size();				  
	string period; 
	string beforeDot, afterDot;
	string _time;
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

*/

