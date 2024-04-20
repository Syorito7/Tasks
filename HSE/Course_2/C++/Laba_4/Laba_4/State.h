#pragma once
//#include "WindowKeeper.h"
//#include "Menu.h"
// ---------------------------
//#include "GameContext.h"
// Добавил, так как IStateManager пользуется классов IState.

// Разница в State.h




#pragma once

#include "WindowKeeper.h"
#include "Menu.h"

class IStateManager;

class IState {
protected:
	IStateManager* m_state_manager;
public:
	IState() = default;
	IState(IStateManager* state_manager) : m_state_manager(state_manager) {};
	virtual bool do_step()
	{
		return true;
	}
};

class IStateManager 
{
public:
	virtual void set_next_state(IState* state) {};
};

class ExitState : public IState
{
public:
	ExitState(IStateManager* state_manager) : IState(state_manager) {};
	bool do_step() override
	{
		return false;
	}
};

class GameState;

class SelectState : public IState, public IWindowKeeper 
{
	Menu m_menu;
public:
	SelectState(IStateManager* state_manager) : IState(state_manager) {};
	SelectState(IStateManager* state_manager, std::string window_title) : IState(state_manager), IWindowKeeper(config::SELECT_LEVEL_VIDEO_MODE, window_title)
	{
		m_menu = Menu(state_manager);
	}
	bool do_step() override
	{
		event_handling();
		m_window.close();
		return true;
	}
	void event_handling() override
	{
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);
					if (m_menu.process_mouse(pos, true))
						return;
				}
				else if (event.type == sf::Event::Closed) {
					//window.close();
				}
				else {
					sf::Vector2f pos(sf::Mouse::getPosition(m_window));
					m_menu.process_mouse(pos, false);
				}
			}
			this->render();
		}
	}
	void render() override 
	{
		m_window.clear(config::SELECT_LEVEL_BACKGROUND_COLOR);
		m_menu.draw_into(m_window);
		m_window.display();
	}
};

class GameState : public IState, public IWindowKeeper {
	ContextManager m_context_manager;
	Maze m_maze;
public:
	GameState(IStateManager* state_manager) : IState(state_manager) {};
	GameState(IStateManager* state_manager, std::string window_title) : IState(state_manager), IWindowKeeper(config::GAME_VIDEO_MODE, window_title) {

	}
	void set_maze(Maze maze) {
		m_maze = maze;
	}
	void set_context(GameContext&& context) {
		m_context_manager.set_context(std::move(context));
		m_context_manager.save_current_context();
	}
	void process_key_pressed(sf::Keyboard::Key code)
	{
		if (m_context_manager.get_context().get_state() != INGAME)
			return;
		if (std::find(config::KEY_DIRS.begin(), config::KEY_DIRS.end(), code) != config::KEY_DIRS.end()) 
		{
			m_context_manager.save_current_context();

			GameContext game = m_context_manager.get_context();

			if (std::find(config::KEY_LEFT.begin(), config::KEY_LEFT.end(), code) != config::KEY_LEFT.end())
				game.move_pacman(LEFT);
			else if (std::find(config::KEY_RIGHT.begin(), config::KEY_RIGHT.end(), code) != config::KEY_RIGHT.end())
				game.move_pacman(RIGHT);
			else if (std::find(config::KEY_UP.begin(), config::KEY_UP.end(), code) != config::KEY_UP.end())
				game.move_pacman(UP);
			else if (std::find(config::KEY_DOWN.begin(), config::KEY_DOWN.end(), code) != config::KEY_DOWN.end())
				game.move_pacman(DOWN);

			m_context_manager.set_context(game);
		}
	}
	void process_event(std::unique_ptr<IGameEvent> ptr_event)
	{
		if (ptr_event == nullptr)
			return;
		GameContext game = m_context_manager.get_context();

		ptr_event->handle(game);

		m_context_manager.set_context(game);
	}
	bool do_step() override
	{
		event_handling();
		m_window.close();

		SelectState* new_state = new SelectState(m_state_manager, config::SELECT_LEVEL_TITLE);
		m_state_manager->set_next_state(new_state);
		return true;
	}
	void event_handling() override {
		sf::Clock clock;
		clock.restart();

		int t = 600 + rand() % 300;

		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
					{
						m_context_manager.restore_previous_context();
						clock.restart();
					}
					else
						process_key_pressed(event.key.code);
				}
				else if (event.type == sf::Event::Closed)
					return;
			}

			if (clock.getElapsedTime().asMilliseconds() >= t && m_context_manager.get_context().get_state() == INGAME)
			{
				GameContext game = m_context_manager.get_context();
				game.move_dynamic_entities();
				m_context_manager.set_context(game);

				clock.restart();
				t = 600 + rand() % 300;
			}

			if (m_context_manager.get_context().get_state() == INGAME)
				this->update();

			this->render();
		}
	}
	void update() override
	{
		this->process_event(m_context_manager.get_context().process_pacman_and_dynamic_entities());
		this->process_event(m_context_manager.get_context().process_pacman_and_static_entities());
		this->process_event(m_context_manager.get_context().is_win());
	}
	void render() override
	{
		if (m_context_manager.get_context().get_state() == INGAME)
			m_window.clear(config::GAME_COLOR_BACKGROUND_INGAME);
		else if (m_context_manager.get_context().get_state() == WIN)
			m_window.clear(config::GAME_COLOR_BACKGROUND_WIN);
		else if (m_context_manager.get_context().get_state() == LOST)
			m_window.clear(config::GAME_COLOR_BACKGROUND_LOST);
		m_maze.draw_into(m_window);
		m_context_manager.get_context().draw_into(m_window);
		m_window.display();
	}
};

void ExitCommand::execute()
{

	m_state_manager->set_next_state(new ExitState(m_state_manager));
}
