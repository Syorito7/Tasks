#pragma once

#include "IMyDrawble.h"



class Room;

// стороны комнаты


class IEntity;

class IRoomSide : public IMyDrawable
{
public:
	virtual void enter(IEntity* entity) = 0;
};


// Комната

class Room : public IMyDrawable
{

	sf::RectangleShape m_rectangle;

	// TO DO: реализовать IRoomSide
	// добавить IRoomSide* m_sides;
	// Стороны комнаты
	IRoomSide* m_sides[4];
public:
	// Прототип draw_into
	void draw_into(sf::RenderWindow& window) override;


	Room(float size)
	{
		// Прописать тело

		sf::Vector2f size_2f(size, size);
		m_rectangle.setSize(size_2f);
		m_rectangle.setOrigin(size_2f * 0.5f);
		m_rectangle.setFillColor(config::GAME_COLOR_ROOM);
	}

	// Реализовать геттеры и сеттеры


	sf::Vector2f get_position() const
	{
		return m_rectangle.getPosition();
	}

	
	Direction get_direction(IRoomSide* ptr_room_side)
	{
		for (size_t i = 0; i < 4; i++)
		{
			// перегрузить оператор ==
			if (m_sides[i] == ptr_room_side)
			{
				return static_cast<Direction>(i);
			}
		}
		return Direction::INVALID;
	}
	

	// ОК!
	bool operator == (const Room& room) const
	{
		return this->get_position() == room.get_position();
	}

	// TO DO: добавить методы

	void set_side(Direction side, IRoomSide* ptr_room_side)
	{
		m_sides[side] = ptr_room_side;
	}

	void set_position(sf::Vector2f position)
	{
		m_rectangle.setPosition(position);
	}

	float get_size()
	{
		return m_rectangle.getSize().x;
	}


	IRoomSide* get_side(Direction side)
	{
		return m_sides[side];
	}

};



class Pass : public IRoomSide
{
	Room* m_room1;
	Room* m_room2;
public:
	// Конструктор
	Pass(Room* m_room1, Room* m_room2) : m_room1(m_room1), m_room2(m_room2) {};

	void draw_into(sf::RenderWindow& window) override {} // от IMYDrawable
	void enter(IEntity* entity) override; // от IRoomSide
};





// 

// проход


class Wall : public IRoomSide {
	Room* m_room;
	// Точки
	sf::Vertex m_line[2];
public:
	Wall(Room* m_room) : m_room(m_room) {};

	void draw_into(sf::RenderWindow& window) override
	{
		Direction dir = m_room->get_direction(this);
		sf::Vector2f pos = m_room->get_position();
		float size = m_room->get_size();
		if (dir == Direction::LEFT)
		{
			m_line[0] = sf::Vector2f(pos.x - size / 2, pos.y + size / 2);
			m_line[1] = sf::Vector2f(pos.x - size / 2, pos.y - size / 2);
		}
		else if (dir == Direction::RIGHT)
		{
			m_line[0] = sf::Vector2f(pos.x + size / 2, pos.y + size / 2);
			m_line[1] = sf::Vector2f(pos.x + size / 2, pos.y - size / 2);
		}
		else if (dir == Direction::UP)
		{
			m_line[0] = sf::Vector2f(pos.x + size / 2, pos.y - size / 2);
			m_line[1] = sf::Vector2f(pos.x - size / 2, pos.y - size / 2);
		}
		else if (dir == Direction::DOWN)
		{
			m_line[0] = sf::Vector2f(pos.x + size / 2, pos.y + size / 2);
			m_line[1] = sf::Vector2f(pos.x - size / 2, pos.y + size / 2);
		}
		else
		{
			return;
		}
		m_line[0].color = config::GAME_COLOR_WALL;
		m_line[1].color = config::GAME_COLOR_WALL;
		window.draw(m_line, 2, sf::Lines);

	}

	void enter (IEntity* entity) override {}
};



// Отрисовка пространства (<,>,^,вниз)
void Room::draw_into(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
	for (auto& ptr_side : m_sides)
	{
		ptr_side->draw_into(window);
	}
}

// Лабиринт


class Maze : public IMyDrawable
{
	std::vector<Room*> m_rooms;
public:
	Maze() = default;
	Maze(std::vector<Room*> m_rooms) : m_rooms(m_rooms) {};

	void draw_into(sf::RenderWindow& window) override
	{
		for (auto& ptr_room : m_rooms)
		{
			ptr_room->draw_into(window);
		}
	}
};
