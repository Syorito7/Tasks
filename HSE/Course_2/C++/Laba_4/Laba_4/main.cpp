#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <iterator>
#include <memory>
#include <xmemory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Application.h"

#include <windows.h>

/*
#include "Menu.h"
#include "Command.h"
#include "Config.h"
#include "Maze.h"
*/
//#include "GameBuilder.h"

int main()
{
    // ���������� ������ ��� ��������������� ������
    config::eat.openFromFile("eat.ogg");
    config::win.openFromFile("win.ogg");
    config::death.openFromFile("death.ogg");
    config::step.openFromFile("move_pacman.ogg");
    config::choice_button.openFromFile("choice.ogg");
    config::exit.openFromFile("exit.ogg");




    // ���������� ������ ��� �������������� ��������
    sf::SoundBuffer main_sound_buffer;// ����� ��� �����
    main_sound_buffer.loadFromFile("main_music.ogg");// ��������� ���� � �����
    sf::Sound main_sound(main_sound_buffer); // ������ ���� �� ������
    main_sound.play(); // ��������������� �����


    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Application app;
    return app.run();
    




    // ������ �� SFML
    /*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
    */
}