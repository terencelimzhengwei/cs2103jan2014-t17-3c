#include "CommandManager.h"

CommandManager::~CommandManager(void){
	Clear();
}

bool CommandManager::CanUndo() const
{
	return (undoList.size() > 0);
}

bool CommandManager::CanRedo() const
{
	return (redoList.size() > 0);
}

int CommandManager::getUndoLevel() const
{
	return m_nUndoLevel;
}

void CommandManager::setUndoLevel(int newValue)
{
	m_nUndoLevel = newValue;
}

bool CommandManager::IsDirty() const
{
	return (m_nCleanCount != 0);
}

Command* CommandManager::getLastUndoCommand() const
{
	return undoList.back();
}

Command* CommandManager::getLastRedoCommand() const
{
	return redoList.back();
}

void CommandManager::DoCommand(Command* pCommand)
{
	if(pCommand->getType()==UNDO){
		Undo();
	}else if(pCommand->getType()==REDO){
		Redo();
	}else{
		// Clear redo list
		if(pCommand->getType()!=DISPLAY){
			ClearRedoList();
		}
		// Execute the command and add it to undo list if succeeded
		if (pCommand->execute(_taskList)){
			if(undoable(pCommand)){
				AddUndo(pCommand);
			}else{
				delete pCommand;
				pCommand=NULL;
			}
		}
	}
}

void CommandManager::Undo()
{
	if (CanUndo())
	{
		m_nCleanCount--;
		Command* pCommand = undoList.back();
		undoList.pop_back();
		if (pCommand->undo(_taskList)){
			AddRedo(pCommand);
		}else{
			delete pCommand;
			pCommand=NULL;
		}
	}
}

void CommandManager::Redo()
{
	if (CanRedo())
	{
		m_nCleanCount++;
		Command* pCommand = redoList.back();
		redoList.pop_back();
		if (pCommand->execute(_taskList)){
			AddUndo(pCommand);
		}else{
			delete pCommand;
			pCommand=NULL;
		}
	}
}

void CommandManager::Clear()
{
	ClearUndoList();
	ClearRedoList();
}

void CommandManager::SetClean()
{
	m_nCleanCount = 0;
}

void CommandManager::AddUndo(Command* pCommand)
{
	if (undoList.size() >= m_nUndoLevel)
	{
		delete undoList.front();
		undoList.pop_front();
	}
	undoList.push_back(pCommand);
	if (m_nCleanCount < 0 && redoList.size() > 0)
		m_nCleanCount = undoList.size() + redoList.size() + 1;
	else
		m_nCleanCount++;
}

void CommandManager::AddRedo(Command* pCommand)
{
	redoList.push_back(pCommand);
}

void CommandManager::ClearUndoList()
{
	ClearCommandList(&undoList);
}

void CommandManager::ClearRedoList()
{
	ClearCommandList(&redoList);
}

void CommandManager::ClearCommandList(std::list<Command*>* pList)
{
	std::list<Command*>::iterator it;
	for (it = pList->begin(); it != pList->end(); it++)
		delete *it;
	pList->erase(pList->begin(), pList->end());
}

bool CommandManager::undoable(Command* pCommand){
	if(pCommand->getType() == ADD){
		return true;
	}else if(pCommand->getType() == DELETE){
		return true;
	}else if(pCommand->getType() == CLEAR){
		return true;
	}else if(pCommand->getType() == UNDONE){
		return true;
	}else if(pCommand->getType() == DONE){
		return true;
	}else if(pCommand->getType() == SEARCH){
		return true;
	}else if(pCommand->getType() == FILTER){
		return true;
	}else if(pCommand->getType() == UNDO){
		return true;
	}else if(pCommand->getType() == EDIT){
		return true;
	}
	return false;
}
