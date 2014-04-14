//@author A0097330H
#ifndef STORAGE_H
#define STORAGE_H

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Constants.h"
#include "Logger.h"
#include "Parser.h"
#include "TaskList.h"

class Storage{
public:
	Storage(void);
	~Storage(void);

	void retrieveFile(TaskList&);
	void saveFile(TaskList&);
	bool isCorrupted();

private:
	std::string _undoneFileName;
	std::string _doneFileName;
	Parser _parser;
	bool _corrupted;
	Logger* _logger;

	void saveUndoneTasks(TaskList&);
	void saveDoneTasks(TaskList&);
	void retrieveDoneTasks(TaskList&);
	void retrieveUndoneTasks(TaskList&);

};
#endif