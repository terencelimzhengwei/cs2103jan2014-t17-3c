#pragma once
#include "Command_Delete.h"

Command_Delete::Command_Delete() {
		init(); 
		setCommandType(DELETE);
}
Command_Delete::~Command_Delete(){};

unsigned long long Command_Delete::getIndex(){ 
		return Command::getIndex();		
}
std::string Command_Delete::getDescription(){
		return Command::getDescription();		
}

