#pragma once

//#include "Config.h"

class IWindowKeeper
{
	// Проверить доступ, пока поставлю protected, так как зависит от двух классов (SelectLevelState и GameState)
protected:
	// Наследник от Window
	sf::RenderWindow m_window;
public:

	// Решена ошибка с конструктором, проблема была в строке main_title, нужно было передать указатель через преобразование в c-строку

	IWindowKeeper() = default;
	IWindowKeeper(sf::VideoMode mode, std::string main_title) : m_window(mode, main_title.c_str())
	{
		// задать FPS - ОK!
		m_window.setFramerateLimit(config::FRAME_RATE_LIMIT);
		m_window.setVerticalSyncEnabled(true);
	}

	// Методы


	virtual void event_handling() {};
	virtual void update() {};
	virtual void render() {}; // Отображение нарисованных объектов в окно
		//m_window.display();
};
