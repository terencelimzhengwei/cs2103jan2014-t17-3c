#pragma once
#ifndef STORAGE_H
#define STORAGE_H

#include "TaskList.h"
#include "Parser.h"
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class Storage
{
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
	bool isCorrupted();

public:
	Storage(void);
	~Storage(void);

	void retrieveFile(TaskList&);
	void saveFile(TaskList&);

	std::string removeFirstWord(std::string);
};
#endif