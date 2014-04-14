#include "CommandManager.h"
//@author A0097277M
CommandManager::~CommandManager(void){
	Clear();
}

bool CommandManager::CanUndo() const{
	return (undoList.size() > ZERO);
}

bool CommandManager::CanRedo() const{
	return (redoList.size() > ZERO);
}

int CommandManager::getUndoLevel() const{
	return allowableUndoLevel;
}

void CommandManager::setUndoLevel(int newValue){
	allowableUndoLevel = newValue;
}

bool CommandManager::IsDirty() const{
	return (UndoRedoCount != ZERO);
}

Command* CommandManager::getLastUndoCommand() const{
	return undoList.back();
}

Command* CommandManager::getLastRedoCommand() const{
	return redoList.back();
}

void CommandManager::DoCommand(Command* pCommand, std::string& feedback){
	if(pCommand->getType() == UNDO){
		Undo(feedback);
	} else if(pCommand->getType() == REDO){
		Redo();
	} else {
		// Clear redo list
		if(pCommand->getType() != DISPLAY){
			ClearRedoList();
		}
		// Execute the command and add it to undo list if succeeded
		if (pCommand->execute(_taskList,feedback)){
			if(undoable(pCommand)){
				AddUndo(pCommand);
			} else {
				delete pCommand;
				pCommand = NULL;
			}
		}
	}
}

void CommandManager::Undo(std::string& feedback){
	if (CanUndo()){
		UndoRedoCount--;
		Command* pCommand = getLastUndoCommand();
		undoList.pop_back();
		if (pCommand->undo(_taskList, feedback)){
			AddRedo(pCommand);
		} else {
			delete pCommand;
			pCommand = NULL;
		}
	}
}

void CommandManager::Redo(){
	std::string feedback;
	if (CanRedo()){
		UndoRedoCount++;
		Command* pCommand = getLastRedoCommand();
		redoList.pop_back();
		if (pCommand->execute(_taskList,feedback)){
			AddUndo(pCommand);
		} else {
			delete pCommand;
			pCommand = NULL;
		}
	}
}

void CommandManager::Clear(){
	ClearUndoList();
	ClearRedoList();
}

void CommandManager::SetClean(){
	UndoRedoCount = ZERO;
}

void CommandManager::AddUndo(Command* pCommand){
	if (undoList.size() >= allowableUndoLevel){
		delete undoList.front();
		undoList.pop_front();
	}
	undoList.push_back(pCommand);
	if (UndoRedoCount < 0 && redoList.size() > ZERO){
		UndoRedoCount = undoList.size() + redoList.size() + INCREMENT_VALUE;
	} else {
		UndoRedoCount++;
	}
}

void CommandManager::AddRedo(Command* pCommand){
	redoList.push_back(pCommand);
}

void CommandManager::ClearUndoList(){
	ClearCommandList(&undoList);
}

void CommandManager::ClearRedoList(){
	ClearCommandList(&redoList);
}

void CommandManager::ClearCommandList(std::list<Command*>* pList){
	std::list<Command*>::iterator it;
	for (it = pList->begin(); it != pList->end(); it++) {
		delete *it;
	}
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
