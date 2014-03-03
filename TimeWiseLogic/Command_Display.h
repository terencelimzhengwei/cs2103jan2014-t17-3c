#pragma once
#include "Command.h"

class Command_Display : public Command
{
public:
	Command_Display(){
		init();
		setCommandType(DISPLAY);
	}
	~Command_Display(void);

	int	getIndex() { 
		return Command::getIndex();		
	}
	void setIndex(int idx){ 
		Command::setIndex(idx);			
	}
};

