#pragma once
#include "Command_Display.h"


Command_Display::Command_Display(){
		init();
		setCommandType(DISPLAY);
}
Command_Display::~Command_Display(){};

unsigned long long Command_Display::getIndex() { 
		return Command::getIndex();		
}
void Command_Display::setIndex(unsigned long long idx){ 
		Command::setIndex(idx);			
}


