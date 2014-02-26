#include "Parser.h"
#include "Constants.h"
#include "Command.h"
#include <string>
using namespace std;

Parser::Parser(void) {
}

Parser::~Parser(void) {
}

Command Parser::interpretCommand(string action) {
	string commandTypeString = getFirstWord(action);
	string description = removeFirstWord(action);

	CMD_TYPE commandType = determineCommandType(commandTypeString);

	switch (commandType) {
	case ADD: 
		Command cmd;
		cmd.setType(commandType); 
		cmd.setDescription(description);
		return cmd;
	}
}

CMD_TYPE Parser::determineCommandType(string commandTypeString) {
	if(commandTypeString == "add") {
		return CMD_TYPE::ADD;
	}
}

string Parser::getFirstWord(string action) {
	unsigned int tStart = 0;
	unsigned int tEnd = 0;

	tEnd = action.find_first_of(" ");

	string userCommand = action.substr(tStart, tEnd - tStart);
	return userCommand;
}

string Parser::removeFirstWord(string action) {
	unsigned int tStart = 0;
	unsigned int tEnd = 0;

	tStart = action.find_first_of(" ") + 1;
	tEnd = action.size();

	string userText = action.substr(tStart, tEnd - tStart);
	return userText;
}