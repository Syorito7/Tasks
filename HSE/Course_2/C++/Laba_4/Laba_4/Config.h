


#pragma once




enum Direction { INVALID = -1, LEFT, RIGHT, UP, DOWN };

enum State { INGAME, WIN, LOST };


namespace config {
    // : Общее
    const unsigned int FRAME_RATE_LIMIT = 60;
    // : Меню
    const sf::Vector2f BUTTON_SIZE = { 250, 100 };
    const size_t BUTTON_FONT_SIZE = static_cast<size_t>(BUTTON_SIZE.y / 1.5f);
    const float BUTTON_FRAME_THICKNESS = 2;
    const char FONT_FILE[] = "Calibri-Light.ttf";
    const char SELECT_LEVEL_TITLE[] = "Select Level";
    const sf::VideoMode SELECT_LEVEL_VIDEO_MODE{ 600, 800 };
    const char BUTTON_TEXT_EASY[] = "Easy";
    const char BUTTON_TEXT_MEDIUM[] = "Medium";
    const char BUTTON_TEXT_HARD[] = "Hard";
    const char BUTTON_TEXT_EXIT[] = "Exit";
    // : Игра
    // const sf::VideoMode GAME_VIDEO_MODE{ 380, 220 };
    const sf::VideoMode GAME_VIDEO_MODE{ 1080, 720 };

    // Разрешение
   // const sf::VideoMode GAME_VIDEO_MODE{ 1920, 1080};
    const char EASY_GAME_TITLE[] = "Level: Easy";
    const char MEDIUM_GAME_TITLE[] = "Level: Medium";
    const char HARD_GAME_TITLE[] = "Level: Hard";
    const float EASY_GAME_ENEMY_RATIO = 0.0f;
    const float MEDIUM_GAME_ENEMY_RATIO = 0.03f;
    const float HARD_GAME_ENEMY_RATIO = 0.07f;
    const float ROOM_SIZE = 50;
    const float GAME_ENEMY_SIZE = ROOM_SIZE * 0.7;
    const float GAME_FOOD_SIZE = ROOM_SIZE * 0.2;

    const sf::Color GAME_COLOR_PACMAN_POWERED_UP = sf::Color::White;
    // : Пакмэн


    const float GAME_PACMAN_SIZE = ROOM_SIZE * 0.8;
    const std::vector<sf::Keyboard::Key> KEY_LEFT = { sf::Keyboard::A, sf::Keyboard::Left };
    const std::vector<sf::Keyboard::Key> KEY_RIGHT = { sf::Keyboard::D, sf::Keyboard::Right };
    const std::vector<sf::Keyboard::Key> KEY_UP = { sf::Keyboard::W, sf::Keyboard::Up };
    const std::vector<sf::Keyboard::Key> KEY_DOWN = { sf::Keyboard::S, sf::Keyboard::Down };
    const std::vector<sf::Keyboard::Key> KEY_DIRS = { sf::Keyboard::A, sf::Keyboard::Left, sf::Keyboard::D, sf::Keyboard::Right, sf::Keyboard::W, sf::Keyboard::Up, sf::Keyboard::S, sf::Keyboard::Down };
    
    // : Набор цветов для спрайтов

    const sf::Color BUTTON_COLOR_TEXT = sf::Color::White;
    const sf::Color BUTTON_COLOR_FILL = sf::Color::Black;
    const sf::Color BUTTON_COLOR_SELECTION = sf::Color{ 50, 50, 100 };
    const sf::Color BUTTON_COLOR_FRAME = sf::Color::Blue;
    const sf::Color SELECT_LEVEL_BACKGROUND_COLOR{ 25, 25, 25 };
    const sf::Color GAME_COLOR_BACKGROUND_INGAME{ 50,50,50 };
    const sf::Color GAME_COLOR_BACKGROUND_WIN{ 0, 100, 0 };
    const sf::Color GAME_COLOR_BACKGROUND_LOST{ 100, 0, 0 };
    const sf::Color GAME_COLOR_PACMAN{ 250, 250, 0 };
    const sf::Color GAME_COLOR_ROOM = sf::Color::Black;
    const sf::Color GAME_COLOR_WALL = sf::Color::Blue;
    const sf::Color GAME_FOOD_COLOR{ 0, 200, 100 };
    const sf::Color GAME_ENEMY_COLOR{ 255, 50, 0 };


    // Музыка
    sf::Music eat;
    sf::Music win;
    sf::Music death;
    sf::Music step;
    sf::Music choice_button;
    sf::Music exit;

}
