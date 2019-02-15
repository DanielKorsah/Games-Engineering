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
std::vector<Bullet*> bullets = std::vector<Bullet*>{};
Player* player;

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

	//rows
	for (int r = 0; r < invaders_rows; ++r)
	{
		auto rect = IntRect(0, 0, 32, 32);

		//columns
		for (int c = 0; c < invaders_columns; ++c)
		{
			Vector2f position = {(50.0f * c+1), (50.0f * r+1)};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}

	player = new Player();
	ships.push_back(player);
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

	for (auto &b : bullets)
	{
		b->Update(dt);
	}

}

void Render(RenderWindow &window) {
	//window.draw(invader);
	for (const auto s : ships) {
		window.draw(*s);
	}

	for (const auto b : bullets) {
		window.draw(*b);
	}
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Ivaders");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
}