#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//For everyone to use, if you have constants to define, define it here

#include <string>
#include <ctime>

static const int CMD_TYPE_COUNT		= 8;
static const int PRIORITY_COUNT			= 3;
static const int TASK_STATUS_COUNT		= 3;
static const int TASK_TYPE_COUNT		= 3;

enum TASK_STATUS{UNDONE,OVERDUE,DONE};
enum TASK_TYPE{TIMED,DEADLINE,FLOATING};
enum CMD_TYPE{ADD,DELETE,EDIT,CLEAR,DISPLAY,SEARCH,FILTER, UNDEFINED};
enum PRIORITY{HIGH,MEDIUM,LOW};

static const std::string CMD_TYPE_STRING[CMD_TYPE_COUNT] =	
{ "add","delete","edit","clear","display","search","filter","undefined"	};
static const std::string PRIORITY_STRING[PRIORITY_COUNT]		=		{"high","medium","low"};
static const std::string TASK_STATUS_STRING[TASK_STATUS_COUNT]	=		{"undone","overdue","done"};
static const std::string TASK_TYPE_STRING[TASK_TYPE_COUNT]		=		{"timed","deadline","floating"};




#endif // !_CONSTANTS_H
