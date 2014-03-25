#pragma once

#include <list>
#include "Command.h"
#include "TaskList.h"

class CommandManager
{
public:
	CommandManager(TaskList& taskList):_taskList(taskList){};
	~CommandManager(void);

	bool CanUndo() const;
	bool CanRedo() const;
	int getUndoLevel() const;
	void setUndoLevel(int newValue);
	bool IsDirty() const;
	Command* getLastUndoCommand() const;
	Command* getLastRedoCommand() const;
	void DoCommand(Command* pCommand);
	void Undo();
	void Redo();
	void Clear();
	void SetClean();

	// Implementations
	void AddUndo(Command* pCommand);
	void AddRedo(Command* pCommand);
	void ClearUndoList();
	void ClearRedoList();
	void ClearCommandList(std::list<Command*>* pList);
	bool undoable(Command* pCommand);
private:
	TaskList& _taskList;
	std::list<Command*>	undoList;
	std::list<Command*>	redoList;
	int m_nUndoLevel;
	int m_nCleanCount;
};

