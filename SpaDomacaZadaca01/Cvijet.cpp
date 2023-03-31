#include "Cvijet.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>

using namespace sf;
using namespace std;

Cvijet::Cvijet(sf::RenderWindow* window)
{
	this->window = window;
}

CircleShape set_background() {
	CircleShape bg(600.f);
	bg.setPosition(-250, -250);
	return bg;
}

CircleShape set_sun() {
	CircleShape sun(50.f);
	sun.setFillColor(sf::Color(255, 255, 0));
	sun.setPosition(40, 40);
	return sun;
}
RectangleShape set_ground() {
	RectangleShape ground(sf::Vector2f(3000.f, 250.f));
	ground.setPosition(-50.f, 500.f);
	ground.setFillColor(sf::Color(150, 75, 0));
	return ground;
}

CircleShape set_body() {
	// circle 
	CircleShape middleCircle(45.f);
	middleCircle.setFillColor(sf::Color(165, 42, 42));
	//obrub 
	middleCircle.setOutlineThickness(25.f);
	middleCircle.setOutlineColor(sf::Color::Yellow);
	//Pozicija	 za circle + obrub
	middleCircle.setPosition(236, 200);
	return middleCircle;
}

ConvexShape set_first_leaf() {
	ConvexShape convexLeaf;
	convexLeaf.setPointCount(4);
	convexLeaf.setPoint(0, sf::Vector2f(30.f, 7.f));
	convexLeaf.setPoint(1, sf::Vector2f(80.f, 3.f));
	convexLeaf.setPoint(2, sf::Vector2f(20.f, 30.f));
	convexLeaf.setPoint(3, sf::Vector2f(0.f, 25.f));
	convexLeaf.setFillColor(sf::Color::Green);
	convexLeaf.setPosition(283, 350);

	return convexLeaf;
}

ConvexShape set_sec_leaf() {
	ConvexShape convexLeaf;
	convexLeaf.setPointCount(4);
	convexLeaf.setPoint(0, sf::Vector2f(-30.f, 7.f));
	convexLeaf.setPoint(1, sf::Vector2f(-80.f, 3.f));
	convexLeaf.setPoint(2, sf::Vector2f(-20.f, 30.f));
	convexLeaf.setPoint(3, sf::Vector2f(0.f, 25.f));
	convexLeaf.setFillColor(sf::Color::Green);
	convexLeaf.setPosition(275, 400);

	return convexLeaf;
}

RectangleShape set_stem() {
	RectangleShape stem(sf::Vector2f(10.f, 185.f));
	stem.setFillColor(sf::Color(0, 110, 0));
	stem.setPosition(275, 315);
	return stem;
}

void play_animation(list<Drawable*> shapes, RenderWindow* window, CircleShape &sun, CircleShape& bg) {
	
	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}
		window->clear();


		for (auto it = shapes.begin(); it!=shapes.end(); ++it)
		{
			//Dvostruko derefenerciranje
			window->draw(**it);
		}

		//Promjena pozadine kad padne sunce
		sun.getPosition().y >= 420 ? bg.setFillColor(sf::Color::Black) : bg.setFillColor(sf::Color(80, 100, 255));
		//Izlazak iz programa kad padne sunce skroz
		if (sun.getPosition().y == 500) {
			window->close();
		}

		//animation
		sun.move(sf::Vector2f(0, 0.5));

		window->display();
	}
}


//Samo komentar da vidim kako je na githubu

void innit(RenderWindow* window) {
	CircleShape bg = set_background();
	RectangleShape stem = set_stem();
	CircleShape body = set_body();
	ConvexShape first_leaf = set_first_leaf(); //UZASAN KOMAD KODA! METODA BI TREBALA BIT JEDAN ZA OBA LEAFA I PRIMAT PARAMETRE.. ALi ih je previse pa cu za sad ovako
	ConvexShape sec_leaf = set_sec_leaf();
	CircleShape sun = set_sun();
	RectangleShape ground = set_ground();


	//radim  Ilistu shapes<Drawable> da bi svaki drawable mogo dernut unutra.
	//Ovo je super jer ne moram mjenjat metodu play_animation da bi dodao nesto novo
	//Na zalost, u cpp ne postoji cista  lista za interface pa moram slat adrese
	list<Drawable*> shapes = {
		&bg,
		&stem,
		&body,
		&first_leaf,
		&sec_leaf,
		&sun,
		&ground};

	
	//Tu saljem sun i bg jer moram sa njima radit animaciju
	play_animation(shapes, window, sun, bg);
}

void Cvijet::draw()
{
	innit(window);
}

