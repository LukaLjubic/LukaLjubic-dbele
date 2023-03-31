#pragma once
#include <SFML/Graphics.hpp>
class Cvijet
{
private:
	sf::RenderWindow* window;
public:
	void draw();
	Cvijet(sf::RenderWindow* window);
};

