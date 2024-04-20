#pragma once

class IStateManager;

class ISelectCommand
{
public:
	virtual void execute() {}

};



class IChangeStateCommand : public ISelectCommand
{
protected:
	IStateManager* m_state_manager;
public:
	IChangeStateCommand(IStateManager* state_manager) : m_state_manager(state_manager) {};
};


class ExitCommand : public IChangeStateCommand
{
public:
	ExitCommand(IStateManager* state_manager) : IChangeStateCommand(state_manager) {};
	void execute() override; // TO DO: написать тело
};

class GameBuilderDirector;

class GameCommand : public IChangeStateCommand
{

	// TO DO:
	// Реализовать класс GameBuilderDirector и объявить указатель (1_*)

	GameBuilderDirector* m_ptr_director;
public:
	GameCommand(IStateManager* state_manager) : IChangeStateCommand(state_manager) {};
	GameCommand(IStateManager* state_manager, GameBuilderDirector* ptr_director) : IChangeStateCommand(state_manager), m_ptr_director(ptr_director) {};
	

	// Запускается, но крашется
	void execute() override; // TO DO: написать тело
};

