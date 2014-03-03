#pragma once
#include "Command.h"

class Command_Delete : public Command
{
public:
	Command_Delete() {
		init(); 
		setCommandType(DELETE);
	}
	~Command_Delete(void);
	int	getIndex(){ 
		return Command::getIndex();		
	}
	std::string	getDescription(){
		return Command::getDescription();		
	}

	int	getIndex() { 
		return Command::getIndex();		
	}
	std::string	getDescription(){ 
		return Command::getDescription();		
	}
};

