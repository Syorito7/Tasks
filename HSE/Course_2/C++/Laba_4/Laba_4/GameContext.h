#pragma once


#include "Maze.h"
//#include "GameBuilder.h"




class IEntity : public IMyDrawable
{
protected:
	Room* m_location;
public:
	// TO DO: Геттеры и сеттеры + методы draw_into

	Room* get_location()
	{
		return m_location;
	}
	void set_location(Room* m_room)
	{
		m_location = m_room;
	}

	void draw_into(sf::RenderWindow& window) override {};
};


void Pass::enter(IEntity* entity)
{
	if (*(entity->get_location()) == *m_room1)
	{
		entity->set_location(m_room2);
	}
	else if (*(entity->get_location()) == *m_room2)
	{
		entity->set_location(m_room1);
	}
}


class GameContext;
class Food;
class Enemy;
class IGameEvent;
class IVisitor;



class IVisitable
{
public:
	virtual std::unique_ptr<IGameEvent> accept(IVisitor* ptr_visitor) = 0;
};


class IStaticEntity : public IEntity, public IVisitable
{
public:
	virtual std::unique_ptr<IStaticEntity> clone() const { return nullptr; };

	std::unique_ptr<IGameEvent> accept(IVisitor* ptr_visitor) override { return nullptr; };

	void draw_into(sf::RenderWindow& window) override {};
	
};

class IDynamicEntity : public IEntity, public IVisitable
{
public:
	virtual std::unique_ptr<IDynamicEntity> clone() const
	{
		return nullptr;
	}

	std::unique_ptr<IGameEvent> accept(IVisitor* ptr_visitor) override
	{
		return nullptr;
	}


	virtual void action() {};
	void draw_into(sf::RenderWindow& window) override {};

};







class IGameEvent {
public:
	virtual void handle(GameContext& game) = 0;
};

// Классы проигрыша и победы

//--------------------------------------------------------

class LostGame : public IGameEvent
{
public:
	void handle(GameContext& game) override;
};

class WinGame : public IGameEvent
{
public:



	void handle(GameContext& game) override;
};

//--------------------------------------------------------
class DeleteStaticEntity : public IGameEvent {
	IStaticEntity* m_ptr_entity;
public:
	DeleteStaticEntity(IStaticEntity* ptr_entity) : m_ptr_entity(ptr_entity) {};
	void handle(GameContext& game) override;
};

//


class DeleteDynamicEntity : public IGameEvent {
	IDynamicEntity* m_ptr_entity;
public:
	DeleteDynamicEntity(IDynamicEntity* ptr_entity) : m_ptr_entity(ptr_entity) {};
	void handle(GameContext& game) override;
};



class IVisitor
{
public:
	virtual std::unique_ptr<IGameEvent> visit(Food* ptr_food) = 0;
	virtual std::unique_ptr<IGameEvent> visit(Enemy* ptr_enemy) = 0;
};

// Пакман. Наследует от IVisitor

class PacMan : public IEntity, public IVisitor {
	bool m_poweredUp = false;
	sf::Clock clock_of_power;
public:


	// Методы

	void set_poweredUp(bool poweredUp)
	{
		m_poweredUp = poweredUp;
	}
	bool is_poweredUp()
	{
		return m_poweredUp;
	}

	void restart_clock_of_power()
	{
		clock_of_power.restart();
	}
	sf::Clock get_clock_of_power()
	{
		return clock_of_power;
	}

	void move(Direction direction)
	{
		m_location->get_side(direction)->enter(this);
	}


	void draw_into(sf::RenderWindow& window) override
	{
		sf::CircleShape pacman(config::GAME_PACMAN_SIZE / 2);
		pacman.setOrigin(sf::Vector2f(config::GAME_PACMAN_SIZE * 0.5f, config::GAME_PACMAN_SIZE * 0.5f));
		pacman.setPosition(m_location->get_position());
		if (m_poweredUp)
		{
			pacman.setFillColor(config::GAME_COLOR_PACMAN_POWERED_UP);
		}
		else
		{
			pacman.setFillColor(config::GAME_COLOR_PACMAN);
		}
		window.draw(pacman);
	}
	

	std::unique_ptr<IGameEvent> visit(Food* ptr_food) override
	{
		return std::make_unique<DeleteStaticEntity>(ptr_food);
	}



	std::unique_ptr<IGameEvent> visit(Enemy* ptr_enemy) override
	{
		if (m_poweredUp)
		{
			return std::make_unique<DeleteDynamicEntity>(ptr_enemy);
		}
		else
		{
			return std::make_unique<LostGame>();
		}
	}


};


// Еда - наследуется от IStaticEntity

class Food : public IStaticEntity
{
public:
	std::unique_ptr<IStaticEntity> clone() const override
	{
		return std::make_unique<Food>(*this);
	}
	std::unique_ptr<IGameEvent> accept(IVisitor* ptr_visitor) override
	{
		return ptr_visitor->visit(this);
	}




	// TO DO: Реализовать draw_into
	void draw_into(sf::RenderWindow& window) override
	{
		sf::CircleShape food(config::GAME_FOOD_SIZE / 2);
		food.setOrigin(sf::Vector2f(config::GAME_FOOD_SIZE * 0.5f, config::GAME_FOOD_SIZE * 0.5f));
		food.setPosition(m_location->get_position());
		food.setFillColor(config::GAME_FOOD_COLOR);
		window.draw(food);
	}
};




class Enemy : public IDynamicEntity {
public:
	std::unique_ptr<IDynamicEntity> clone() const override
	{
		return std::make_unique<Enemy>(*this);
	}

	void action() override
	{
		m_location->get_side(static_cast<Direction>(rand() % 4))->enter(this);
	}
	std::unique_ptr<IGameEvent> accept(IVisitor* ptr_visitor) override
	{
		return ptr_visitor->visit(this);
	}



	// TO DO: Реализовать draw_into
	void draw_into(sf::RenderWindow& window) override
	{
		sf::RectangleShape enemy(sf::Vector2f(config::GAME_ENEMY_SIZE, config::GAME_ENEMY_SIZE));
		enemy.setOrigin(enemy.getSize() * 0.5f);
		enemy.setPosition(m_location->get_position());
		enemy.setFillColor(config::GAME_ENEMY_COLOR);
		window.draw(enemy);
	}
};



// TO DO: Гроб!!!

class GameContext
{
	// Создать вектора указателей динам. и стат. обектов
	std::vector<IDynamicEntity*> dynamic_objects;
	std::vector<IStaticEntity*> static_objects;

	PacMan pacman;
	State state = INGAME;

	int m_points;

public:

	// Конструкторы
	GameContext() = default;
	GameContext(const GameContext& tmp)
	{
		this->m_points = tmp.m_points;
		this->state = tmp.state;
		dynamic_objects.clear();
		for (const auto& dynamicObj : tmp.dynamic_objects) {
			dynamic_objects.push_back(dynamicObj);
		}
		static_objects.clear();
		for (const auto& staticObj : tmp.static_objects) {
			static_objects.push_back(staticObj);
		}
		this->pacman = tmp.pacman;
	}

	// Оператор присваивания
	GameContext& operator=(const GameContext& tmp)
	{
		// Проверка, что А = А
		if (this == &tmp)
		{
			return *this;
		}

		this->state = tmp.state;
		dynamic_objects.clear();

		// Перенос объектов (и стат и динам) в вектора
		for (const auto& dynamicObj : tmp.dynamic_objects) {
			dynamic_objects.push_back(dynamicObj);
		}
		static_objects.clear();
		for (const auto& staticObj : tmp.static_objects) {
			static_objects.push_back(staticObj);
		}
		this->pacman = tmp.pacman;
		return *this;
	}


	std::unique_ptr<GameContext> clone() const
	{
		return std::make_unique<GameContext>(*this);
	}

	// Геттеры и сеттеры

	State get_state()
	{
		return state;
	}
	void set_state(State state)
	{
		this->state = state;
	}

	void set_pacman(Room* room)
	{
		this->pacman.set_location(room);
	}


	// Добавление еды и врагов

	void add_enemy(Room* room)
	{
		IDynamicEntity* enemy = new Enemy;
		enemy->set_location(room);
		dynamic_objects.push_back(enemy);
	}
	void add_food(Room* room)
	{
		IStaticEntity* food = new Food;
		food->set_location(room);
		static_objects.push_back(food);
	}

	// Отрисовка
	void draw_into(sf::RenderWindow& window)
	{
		for (auto& static_object : static_objects)
		{
			static_object->draw_into(window);
		}
		pacman.draw_into(window);
		for (auto& dynamic_object : dynamic_objects)
		{
			dynamic_object->draw_into(window);
		}
	}

	// методы - движения
	void move_pacman(Direction direction)
	{
		config::step.stop();
		config::step.play();

		pacman.move(direction);
	}
	void move_dynamic_entities()
	{
		for (auto& ptr_dynamic_object : dynamic_objects)
		{
			ptr_dynamic_object->action();
		}
	}


	std::unique_ptr<IGameEvent> process_pacman_and_dynamic_entities()
	{
		for (auto& ptr_dynamic_object : dynamic_objects) 
		{
			if (*(pacman.get_location()) == *(ptr_dynamic_object->get_location()))
			{
				return ptr_dynamic_object->accept(&pacman);
			}
		}
		return nullptr;
	}
	std::unique_ptr<IGameEvent> process_pacman_and_static_entities()
	{
		for (auto& ptr_static_object : static_objects)
		{
			if (*(pacman.get_location()) == *(ptr_static_object->get_location()))
			{
				return ptr_static_object->accept(&pacman);
			}
		}
		return nullptr;
	}

	void erase_static_entity(IStaticEntity* static_entity)
	{
		static_objects.erase(std::remove(static_objects.begin(), static_objects.end(), static_entity), static_objects.end());
	}

	// Проверка на победу - когда статичных предметов (еды) нету
	std::unique_ptr<IGameEvent> is_win()
	{
		if (static_objects.size() == 0)
		{
			
			return std::make_unique<WinGame>();
		}
		return nullptr;
	}


	void poweresUp_pacman()
	{
		pacman.set_poweredUp(true);
		pacman.restart_clock_of_power();
	}
	void unpoweresUp_pacman() 
	{
		pacman.set_poweredUp(false);
	}
	bool is_pacman_poweredUp()
	{
		return pacman.is_poweredUp();
	}



	void erase_dynamic_entity(IDynamicEntity* dynamic_entity)
	{
		dynamic_objects.erase(std::remove(dynamic_objects.begin(), dynamic_objects.end(), dynamic_entity), dynamic_objects.end());
	}



	int get_points()
	{
		return m_points;
	}





};


// Показ проигрыша/ выйграша

void LostGame::handle(GameContext& game)
{
	config::death.stop();
	config::death.play();

	game.set_state(LOST);
}

void WinGame::handle(GameContext& game)
{
	config::win.stop();
	config::win.play();

	game.set_state(WIN);
}

void DeleteStaticEntity::handle(GameContext& game)
{
	config::eat.stop();
	config::eat.play();
	// Вызов звука поедания
	game.erase_static_entity(m_ptr_entity);

}



void DeleteDynamicEntity::handle(GameContext& game)
{
	game.erase_dynamic_entity(m_ptr_entity);
}


// TO DO: ContextManager

class ContextManager
{
	std::stack <GameContext> m_history;
	GameContext m_context;
public:
	// Конструкторы
	ContextManager() = default;
	ContextManager(const ContextManager& tmp)
	{
		this->m_history = tmp.m_history;
		this->m_context = tmp.m_context;
	}


	// Методы - работа со стеком

	void save_current_context()
	{
		m_history.push(m_context);
	}

	void restore_previous_context()
	{
		if (m_history.size() == 1)
		{
			m_context = *(m_history.top().clone());
			return;
		}

		m_context = std::move(m_history.top());
		m_history.pop();
	}

	// Реализовать методы, также геттеры и сеттеры

	// Геттеры и сеттеры

	void set_context(GameContext context)
	{
		this->m_context = context;
	}

	GameContext get_context()
	{
		return m_context;
	}

};




