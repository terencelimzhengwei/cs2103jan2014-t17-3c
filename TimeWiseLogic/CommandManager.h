#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H
//@author A0097277M
#pragma once

#include <list>
#include "Command.h"
#include "TaskList.h"
//***************************************************************************
// This class is responsible for managing the undoing and redoing of the
// abstract commands and execution of the commands
//***************************************************************************
class CommandManager{
public: 
	//in the constructor, the allowableUndoLevel is set to 10, which means that 
	//the users can undo a maximum number of 10 times
	CommandManager(TaskList& taskList):_taskList(taskList),allowableUndoLevel(10){};
	~CommandManager(void);

	//Check whether the undoList and redoList are empty
	bool CanUndo() const;
	bool CanRedo() const;

	//getter and setter for allowableUndoLevel
	int getUndoLevel() const;
	void setUndoLevel(int);

	//Check if the undoList contains commands to undo
	bool IsDirty() const;

	//Get the command at the back of the list to undo/redo
	Command* getLastUndoCommand() const;
	Command* getLastRedoCommand() const;

	//Execute the command and assign a message to the feedback string
	void DoCommand(Command*, std::string&);

	//Carry out undoing and redoing of command
	void Undo(std::string&);
	void Redo();

	//remove all the commands in the two lists
	void Clear();
	void SetClean();

	// Add commands to the respective list
	void AddUndo(Command*);
	void AddRedo(Command*);

	void ClearUndoList();
	void ClearRedoList();
	void ClearCommandList(std::list<Command*>*);

	//Check whether the command is undoable
	bool undoable(Command*);
private:
	TaskList& _taskList;
	//Contains all commands that can be undone/redone.
	//The next command to be undone/redone is at the back of the list
	std::list<Command*>	undoList;
	std::list<Command*>	redoList;
	unsigned int allowableUndoLevel;
	int m_nCleanCount;
};
#endif
