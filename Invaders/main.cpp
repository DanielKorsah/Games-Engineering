#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "Ship.h"
#include "game.h"

using namespace sf;
using namespace std;



sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship *> ships = std::vector<Ship*>{};

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

	Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), {100,100});
	ships.push_back(inv);
}

void Update(RenderWindow &window)
{
	// Reset clock, recalculate deltatime
	static Clock clock;

	Event event;
	while (window.pollEvent(event)) 
	{
		if (event.type == Event::Closed) 
		{
			window.close();
			return;
		}
	}

	float dt = clock.restart().asSeconds();
	
	for(auto &s : ships)
	{
		s->Update(dt);
	}

}

void Render(RenderWindow &window) {
	//window.draw(invader);
	for (const auto s : ships) {
		window.draw(*s);
	}
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
}