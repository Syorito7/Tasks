#pragma once

/*
#include "GameContext.h"
#include "Menu.h"
#include "Maze.h"
#include <vector>
*/



class IGameBuilder
{
protected:
	float m_width;
	float m_height;
	float m_romm_size;
	std::vector<std::vector<Room*>> m_rooms;
	GameContext m_context;
	GameState* m_game_state;
public:
	IGameBuilder(float width, float height, float romm_size) : m_width(width), m_height(height), m_romm_size(romm_size) {}
	virtual void create_rooms() {}
	virtual void set_rooms_sides() {}
	void create_context(float dynamic_objects_ratio)
	{
		std::vector<Room*> rooms;
		for (const auto& vec : m_rooms) 
		{
			rooms.insert(rooms.end(), vec.begin(), vec.end());
		}

		int pacmam_pos = rand() % (rooms.size());
		m_context.set_pacman(rooms[pacmam_pos]);
		rooms.erase(rooms.begin() + pacmam_pos);

		int n_enemies = rooms.size() * dynamic_objects_ratio;
		for (int i = 0; i < n_enemies; i++) {
			int enemy_pos = rand() % (rooms.size());
			m_context.add_enemy(rooms[enemy_pos]);
			rooms.erase(rooms.begin() + enemy_pos);
		}

		for (auto& room : rooms) {
			m_context.add_food(room);
		}
	}
	void create_state(IStateManager* state_manager, std::string window_title)
	{
		m_game_state = new GameState(state_manager, window_title);
	}
	void set_all_to_state()
	{
		std::vector<Room*> rooms;
		for (const auto& vec : m_rooms)
		{
			rooms.insert(rooms.end(), vec.begin(), vec.end());
		}
		m_game_state->set_maze(Maze{ rooms });
		m_game_state->set_context(std::move(m_context));
	}
	GameState* get_game()
	{
		return m_game_state;
	}
	Room* room_with_same_pos(Room r)
	{
		for (int i = 0; i < m_rooms.size(); i++)
		{
			for (int j = 0; j < m_rooms[i].size(); j++)
			{
				if (*m_rooms[i][j] == r)
					return m_rooms[i][j];
			}
		}
		return nullptr;
	}
};

class SimpleGameBuilder : public IGameBuilder
{
public:
	SimpleGameBuilder(float width, float height, float romm_size) : IGameBuilder(width, height, romm_size)
	{

	}
	void create_rooms() override
	{
		int n_width = m_width / m_romm_size;
		int n_height = m_height / m_romm_size;
		for (int i = 0; i < n_height; i++) {
			std::vector<Room*> st;
			m_rooms.push_back(st);
			for (int j = 0; j < n_width; j++)
			{
				Room* r = new Room(m_romm_size);
				r->set_position(sf::Vector2f((m_width - m_romm_size * n_width) / 2 + m_romm_size / 2 + m_romm_size * j, (m_height - m_romm_size * n_height) / 2 + m_romm_size / 2 + m_romm_size * i));
				m_rooms[i].push_back(r);
			}
		}
	}
	void set_rooms_sides() override
	{
		for (int i = 0; i < m_rooms.size(); i++)
		{
			for (int j = 0; j < m_rooms[i].size(); j++)
			{
				Room r(m_rooms[i][j]->get_size());

				if (i == 0)
					m_rooms[i][j]->set_side(UP, new Wall{ m_rooms[i][j] });
				else {
					r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x, m_rooms[i][j]->get_position().y - m_romm_size));
					m_rooms[i][j]->set_side(UP, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				}

				if (i == m_rooms.size() - 1)
					m_rooms[i][j]->set_side(DOWN, new Wall{ m_rooms[i][j] });
				else {
					r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x, m_rooms[i][j]->get_position().y + m_romm_size));
					m_rooms[i][j]->set_side(DOWN, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				}

				if (j == 0)
					m_rooms[i][j]->set_side(LEFT, new Wall{ m_rooms[i][j] });
				else {
					r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x - m_romm_size, m_rooms[i][j]->get_position().y));
					m_rooms[i][j]->set_side(LEFT, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				}

				if (j == m_rooms[i].size() - 1)
					m_rooms[i][j]->set_side(RIGHT, new Wall{ m_rooms[i][j] });
				else {
					r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x + m_romm_size, m_rooms[i][j]->get_position().y));
					m_rooms[i][j]->set_side(RIGHT, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				}
			}
		}
	}
};

class ComplexGameBuilder : public IGameBuilder
{
public:
	ComplexGameBuilder(float width, float height, float romm_size) : IGameBuilder(width, height, romm_size) {

	}
	void create_rooms() override
	{
		int n_width = m_width / m_romm_size;
		int n_height = m_height / m_romm_size;
		for (int i = 0; i < n_height; i++)
		{
			std::vector<Room*> st;
			m_rooms.push_back(st);
			for (int j = 0; j < n_width; j++)
			{
				if ((i + 1) % 2 == 0) {
					Room* r = new Room(m_romm_size);
					r->set_position(sf::Vector2f((m_width - m_romm_size * n_width) / 2 + m_romm_size / 2 + m_romm_size * j, (m_height - m_romm_size * n_height) / 2 + m_romm_size / 2 + m_romm_size * i));
					m_rooms[i].push_back(r);
				}
				else {
					if ((j + 1) % 2 == 0) {
						Room* r = new Room(m_romm_size);
						r->set_position(sf::Vector2f((m_width - m_romm_size * n_width) / 2 + m_romm_size / 2 + m_romm_size * j, (m_height - m_romm_size * n_height) / 2 + m_romm_size / 2 + m_romm_size * i));
						m_rooms[i].push_back(r);
					}
				}
			}
		}
	}
	bool is_room_in(Room r)
	{
		for (int i = 0; i < m_rooms.size(); i++) {
			for (int j = 0; j < m_rooms[i].size(); j++) {
				if (*m_rooms[i][j] == r)
					return true;
			}
		}
		return false;
	}
	void set_rooms_sides() override 
	{
		for (int i = 0; i < m_rooms.size(); i++) {
			for (int j = 0; j < m_rooms[i].size(); j++) {
				Room r(m_rooms[i][j]->get_size());

				r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x, m_rooms[i][j]->get_position().y - m_romm_size));
				if (is_room_in(r))
					m_rooms[i][j]->set_side(UP, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				else
					m_rooms[i][j]->set_side(UP, new Wall{ m_rooms[i][j] });

				r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x, m_rooms[i][j]->get_position().y + m_romm_size));
				if (is_room_in(r))
					m_rooms[i][j]->set_side(DOWN, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				else
					m_rooms[i][j]->set_side(DOWN, new Wall{ m_rooms[i][j] });

				r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x - m_romm_size, m_rooms[i][j]->get_position().y));
				if (is_room_in(r))
					m_rooms[i][j]->set_side(LEFT, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				else
					m_rooms[i][j]->set_side(LEFT, new Wall{ m_rooms[i][j] });

				r.set_position(sf::Vector2f(m_rooms[i][j]->get_position().x + m_romm_size, m_rooms[i][j]->get_position().y));
				if (is_room_in(r))
					m_rooms[i][j]->set_side(RIGHT, new Pass{ m_rooms[i][j], room_with_same_pos(r) });
				else
					m_rooms[i][j]->set_side(RIGHT, new Wall{ m_rooms[i][j] });
			}
		}
	}
};

class GameBuilderDirector
{
protected:
	IGameBuilder* m_ptr_builder;
	float m_dynamic_objects_ratio;
	std::string m_window_title;
public:
	GameBuilderDirector(IGameBuilder* ptr_builder, std::string window_title, float dynamic_objects_ratio) : m_ptr_builder(ptr_builder), m_window_title(window_title), m_dynamic_objects_ratio(dynamic_objects_ratio) {}
	GameState* build(IStateManager* state_manager) 
	{
		m_ptr_builder->create_rooms();
		m_ptr_builder->set_rooms_sides();
		m_ptr_builder->create_context(m_dynamic_objects_ratio);
		m_ptr_builder->create_state(state_manager, m_window_title);
		m_ptr_builder->set_all_to_state();
		return m_ptr_builder->get_game();
	}
};


Menu::Menu(IStateManager* state_manager) : m_state_manager(state_manager)
{
	sf::Vector2f button_center_pos(config::SELECT_LEVEL_VIDEO_MODE.width / 2, config::SELECT_LEVEL_VIDEO_MODE.height / 8);
	Button* easy = new Button(button_center_pos, config::BUTTON_SIZE, config::BUTTON_TEXT_EASY, config::BUTTON_FONT_SIZE, new GameCommand(state_manager, new GameBuilderDirector(new SimpleGameBuilder(config::GAME_VIDEO_MODE.width, config::GAME_VIDEO_MODE.height, config::ROOM_SIZE), config::EASY_GAME_TITLE, config::EASY_GAME_ENEMY_RATIO)));
	m_buttons.push_back(easy);

	button_center_pos.y += config::SELECT_LEVEL_VIDEO_MODE.height / 4;
	Button* medium = new Button(button_center_pos, config::BUTTON_SIZE, config::BUTTON_TEXT_MEDIUM, config::BUTTON_FONT_SIZE, new GameCommand(state_manager, new GameBuilderDirector(new SimpleGameBuilder(config::GAME_VIDEO_MODE.width, config::GAME_VIDEO_MODE.height, config::ROOM_SIZE), config::MEDIUM_GAME_TITLE, config::MEDIUM_GAME_ENEMY_RATIO)));
	m_buttons.push_back(medium);

	button_center_pos.y += config::SELECT_LEVEL_VIDEO_MODE.height / 4;
	Button* hard = new Button(button_center_pos, config::BUTTON_SIZE, config::BUTTON_TEXT_HARD, config::BUTTON_FONT_SIZE, new GameCommand(state_manager, new GameBuilderDirector(new ComplexGameBuilder(config::GAME_VIDEO_MODE.width, config::GAME_VIDEO_MODE.height, config::ROOM_SIZE), config::HARD_GAME_TITLE, config::HARD_GAME_ENEMY_RATIO)));
	m_buttons.push_back(hard);

	button_center_pos.y += config::SELECT_LEVEL_VIDEO_MODE.height / 4;
	Button* exit = new Button(button_center_pos, config::BUTTON_SIZE, config::BUTTON_TEXT_EXIT, config::BUTTON_FONT_SIZE, new ExitCommand(state_manager));
	m_buttons.push_back(exit);
}

void GameCommand::execute()
{
	m_state_manager->set_next_state(m_ptr_director->build(m_state_manager));
}

