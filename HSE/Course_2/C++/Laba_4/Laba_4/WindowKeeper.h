#pragma once

//#include "Config.h"

class IWindowKeeper
{
	// ��������� ������, ���� �������� protected, ��� ��� ������� �� ���� ������� (SelectLevelState � GameState)
protected:
	// ��������� �� Window
	sf::RenderWindow m_window;
public:

	// ������ ������ � �������������, �������� ���� � ������ main_title, ����� ���� �������� ��������� ����� �������������� � c-������

	IWindowKeeper() = default;
	IWindowKeeper(sf::VideoMode mode, std::string main_title) : m_window(mode, main_title.c_str())
	{
		// ������ FPS - �K!
		m_window.setFramerateLimit(config::FRAME_RATE_LIMIT);
		m_window.setVerticalSyncEnabled(true);
	}

	// ������


	virtual void event_handling() {};
	virtual void update() {};
	virtual void render() {}; // ����������� ������������ �������� � ����
		//m_window.display();
};
