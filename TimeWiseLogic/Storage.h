#pragma once

//To be done by Jianxiang

class Storage
{
public:
	Storage(void);
	~Storage(void);
};

//Example?
/*//@author A0085616Y
// This class will save the items in the tasklist into a text file
// when user presses "Alt+Q" to quit Managge. It will also load the
// text file back into the tasklist when user launches Managge.
// 
// The constructor for this class will take in the filename parameter
// as a string. This is created within the program and user will not
// have access to the text file, nor change the filename.
//
// Tasks are stored in the text file in the following order:
// taskType [DEADLINE = 0, TIMED = 1, FLOATING = 2]
// task
// schedule (only for deadline and timed schedules)
// status of task [DONE = 0, PENDING = 1, MISSED = 2]
//


#ifndef _FILEPROCESS_H_
#define _FILEPROCESS_H_

#include <iostream>
#include <fstream>
#include "schedulebuilder.h"
#include "tasklist.h"


class FileProcessing{
private:
string _fileName;

public:

//Create new list with name of source text file
FileProcessing();

void insertSpace(ofstream&);

void getTimedDeadFromText(ifstream&, string&, string&, string&, string&);

void getFloatFromText(ifstream&, string&, string&, string&);

STATUS_TYPE getStatusType(string&, STATUS_TYPE&);

void checkTimedSchedule(TimedSchedule&, string&, string&, STATUS_TYPE&, TaskList&);

void checkDeadSchedule(DeadlineSchedule&, string&, string&, STATUS_TYPE&, TaskList&);

void writeTypeAndTask(ofstream&, Task*, TASK_TYPE&);

void writeDeadline(ofstream&,Task*);

void writeTimed(ofstream&, Task*);

void writeStatus(ofstream&, Task*);

void loadFromFile(TaskList&);

void writeToFile(TaskList&);
};

#endif*/

/*//@author A0085616Y
#include "fileprocessing.h"

FileProcessing::FileProcessing(){
_fileName = "Storage.txt";
}

void FileProcessing::insertSpace(ofstream& writeFile){
writeFile << endl;
}

void FileProcessing::getTimedDeadFromText(ifstream& readFile, string& task, string& deadSched, string& status, string& space){
getline(readFile, task);
getline(readFile, deadSched);
getline(readFile, status);
getline(readFile, space);
}

void FileProcessing::getFloatFromText(ifstream& readFile, string& task, string& status, string& space){
getline(readFile, task);
getline(readFile, status);
getline(readFile, space);
}

STATUS_TYPE FileProcessing::getStatusType(string& status, STATUS_TYPE& statusOfTask){
int statusInt;

statusInt = stoi(status);

if(statusInt == DONE){
statusOfTask = DONE;
}
else if(statusInt == PENDING){
statusOfTask = PENDING;
}
else if(statusInt == MISSED){
statusOfTask = MISSED;
}

return statusOfTask;
}

void FileProcessing::checkTimedSchedule(TimedSchedule& tSchedule, string& task, string& status, STATUS_TYPE& statusOfTask, TaskList& taskList){
if(tSchedule.isValidSchedule() && !tSchedule.isEmptySchedule()){
getStatusType(status, statusOfTask);
taskList.add(tSchedule, task, statusOfTask);
}
}

void FileProcessing::checkDeadSchedule(DeadlineSchedule& dSchedule, string& task, string& status, STATUS_TYPE& statusOfTask, TaskList& taskList){
if(dSchedule.isValidSchedule() && !dSchedule.isEmptySchedule()){
getStatusType(status, statusOfTask);
taskList.add(dSchedule, task, statusOfTask);
}
}

void FileProcessing::writeTypeAndTask(ofstream& writeFile, Task* task, TASK_TYPE& checkType){
writeFile << checkType << endl;
string taskString = task->getAction();
writeFile << taskString << endl;
}

void FileProcessing::writeDeadline(ofstream& writeFile, Task* task){
DeadlineSchedule dSchedule = task->getDSchedule();

if(dSchedule.isValidSchedule() && !(dSchedule.isEmptySchedule())) {
string dScheduleString = dSchedule.getScheduleInString();
writeFile << dScheduleString << endl;
}
}

void FileProcessing::writeTimed(ofstream& writeFile, Task* task){
TimedSchedule tSchedule = task->getTSchedule();
if(tSchedule.isValidSchedule() && !(tSchedule.isEmptySchedule())) {
string tScheduleString = tSchedule.getScheduleInString();
writeFile << tScheduleString << endl;
}
}

void FileProcessing::writeStatus(ofstream& writeFile, Task* task){
int status = (*task).getStatus();
writeFile << status << endl;
}

void FileProcessing::loadFromFile(TaskList& taskList){
int typeTask;
string task, typeOfTask, deadSched, timedSched, status, space;
DeadlineSchedule dSchedule;
TimedSchedule tSchedule;
ScheduleBuilder buildSchedule;
STATUS_TYPE statusOfTask;
ifstream readFile(_fileName);

if(readFile.is_open()) {
while(getline(readFile, typeOfTask)) {

try{
typeTask = stoi(typeOfTask);

switch (typeTask) {
case DEADLINE:
try{
getTimedDeadFromText(readFile, task, deadSched, status, space);
dSchedule = buildSchedule.buildDeadlineSchedule(deadSched);
checkDeadSchedule(dSchedule, task, status, statusOfTask, taskList);
}
catch(exception&){
taskList.clearAll();
return;
}
break;

case TIMED:
try{
getTimedDeadFromText(readFile, task, timedSched, status, space);
tSchedule = buildSchedule.buildTimedSchedule(timedSched);
checkTimedSchedule(tSchedule, task, status, statusOfTask, taskList);
}
catch(exception&){
taskList.clearAll();
return;
}
break;

case FLOATING:
try{
getFloatFromText(readFile, task, status, space);
getStatusType(status, statusOfTask);
taskList.add(task, statusOfTask);
}
catch(exception&){
taskList.clearAll();
return;
}

break;

default:
break;
}
}
catch(exception&){
taskList.clearAll();
return;
}
}
}

readFile.close();
}

void FileProcessing::writeToFile(TaskList& taskList){
ofstream writeFile;
writeFile.open(_fileName);
Task* task;
TASK_TYPE checkType;

if(writeFile.is_open())	{
if(taskList.getListSize() != 0)	{
for(int i = taskList.getListSize()-1; i >= 0 ; i--)	{

task = taskList.getTaskAsPointerAt(i);
checkType = task->getType();

switch(checkType) {			
case DEADLINE:

writeTypeAndTask(writeFile, task, checkType);
writeDeadline(writeFile, task);
writeStatus(writeFile, task);
break;

case TIMED:

writeTypeAndTask(writeFile, task, checkType);
writeTimed(writeFile, task);
writeStatus(writeFile, task);
break;

case FLOATING:

writeTypeAndTask(writeFile, task, checkType);
writeStatus(writeFile, task);
break;

default:
break;
}

insertSpace(writeFile);
}
}
}

writeFile.close();
}*/
