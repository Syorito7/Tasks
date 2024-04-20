#pragma once

#include "Config.h"
#include "GameContext.h"
#include "State.h"
#include "GameBuilder.h"
#include <Windows.h>

/*
#include "State.h"
#include "Config.h"
#include "GameContext.h"
#include "GameBuilder.h"
*/

// Наследуется от IStateManager

class Application: public IStateManager
{
private:
	// TO DO:
	// Понять,откуда берётся текущее состояние для m_ptr_state_current
	IState* m_ptr_state_current = new SelectState(this,config::SELECT_LEVEL_TITLE);
	IState* m_ptr_state_next = nullptr;
public:

	void set_next_state(IState* state) override
	{
		m_ptr_state_next = state;
	}
	
	int run()
	{
		sf::Music good;
		good.openFromFile("good.ogg");
		good.play();
		sf::Music theme;
		theme.openFromFile("theme.ogg");
		theme.play();
		theme.setLoop(true);
		// Взято из условия ЛР
		try {
			while (m_ptr_state_current->do_step())
				apply_deffer_state_change();
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << '\n';
			return 1;
		}
		catch (...) {
			std::cout << "Unknown exception\n";
			return 2;
		}

		// Выход из меню
		theme.stop();
		config::exit.play();
		Sleep(2100);
		return 0;
	}

	void apply_deffer_state_change()
	{
		// Переход текущего ptr на следующий?
		m_ptr_state_current = m_ptr_state_next;
	}
};