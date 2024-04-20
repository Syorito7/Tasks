#pragma once

#include "Command.h"
//#include "Config.h"
//#include "IMyDrawble.h"

/*
* ����� Button ��� �������� � ����, ��� ��� ����� ����������� include ���� � �����, 
* ������ �������� ��� ���������� config
*/




class Button : public IMyDrawable
{
	// TO DO: Create ISelectCommand - ��!
	ISelectCommand* m_ptr_command;
	bool m_is_selected = false;
	// ��� ���������
	sf::Font m_font;
	sf::Text m_text;
	// ������������� - ��� �������� ������
	sf::RectangleShape m_rectangle;
public:
	// TO DO:
	// ����������� - ��!
	
	Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, std::string text, size_t font_size, ISelectCommand* m_ptr_command) : m_ptr_command(m_ptr_command)
	{
		// �������������� ������
		m_rectangle.setSize(button_size);
		m_rectangle.setOrigin(button_size * 0.5f);
		// ������� (�����)
		m_rectangle.setPosition(button_center_pos);
		// �����
		m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
		m_rectangle.setOutlineThickness(config::BUTTON_FRAME_THICKNESS);
		m_rectangle.setOutlineColor(config::BUTTON_COLOR_FRAME);

		// ���������� - ������!!!

		// Calibri-Light.ttf ������

		// ������ ��������

		// �������� ���� � ������ SFML - �� ����� ������ ���� -d

		m_font.loadFromFile(config::FONT_FILE);
		m_text.setFont(m_font);
		m_text.setCharacterSize(font_size);
		m_text.setString(text.c_str());
		m_text.setFillColor(config::BUTTON_COLOR_TEXT);


		sf::FloatRect textBounds = m_text.getLocalBounds();
		m_text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
		m_text.setPosition(m_rectangle.getPosition().x, m_rectangle.getPosition().y);

	}

	void select()
	{
		m_is_selected = true;
		m_rectangle.setFillColor(/*������� ���� - ������ ���� Color*/config::BUTTON_COLOR_SELECTION); // Color - LightCoral
	}

	void unselect()
	{
		m_is_selected = false;
		m_rectangle.setFillColor(/*������� ���� - ������ ���� Color*/config::BUTTON_COLOR_FILL); // Color - Salmon
	}

	bool is_selected()
	{
		return m_is_selected;
	}

	bool is_position_in(sf::Vector2f pos)
	{
		// ������������ �������� https://habr.com/ru/articles/739584/


		sf::FloatRect bounds = m_rectangle.getGlobalBounds();

		// ���������� �� ���� ������������� ����� �������
		return bounds.contains(pos);
	}


	// TO DO: ����� ������ ���� ISelectCommand
	void push()
	{
		config::choice_button.stop();
		config::choice_button.play();
		
		m_ptr_command->execute();
	}

	// ���������
	void draw_into(sf::RenderWindow& window) override
	{
		window.draw(m_rectangle);
		window.draw(m_text);
	}
};


class Menu : public IMyDrawable
{
protected:
	std::vector<Button*> m_buttons;
	IStateManager* m_state_manager;
public:
	// ����������� �� ��������� ��� SelectState
	Menu() = default;
	Menu(IStateManager* m_state_manager);

	// ����� process_mouse ...

	int process_mouse(sf::Vector2f pos, bool is_pressed)
	{
		for (auto& ptr_button : m_buttons)
		{
			if (ptr_button->is_position_in(pos))
			{
				if (is_pressed)
				{
					ptr_button->push();
					return 1;
				}
				else
				{
					ptr_button->select();
				}
			}
			else if (ptr_button->is_selected())
			{
				ptr_button->unselect();
			}
		}
		return 0;
	}



	void draw_into(sf::RenderWindow& window) override
	{
		for (auto& ptr_button : m_buttons)
		{
			ptr_button->draw_into(window);
		}
	}
};