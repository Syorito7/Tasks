#pragma once


// Класс, от которого будет наследоваться Menu

class IMyDrawable
{
public:
	virtual void draw_into(sf::RenderWindow& window) = 0;
	virtual ~IMyDrawable() = default;
};
