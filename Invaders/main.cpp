#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "Ship.h";

using namespace sf;
using namespace std;



sf::Texture spritesheet;
sf::Sprite invader;
vector<Ship *> ships;

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Update(RenderWindow &window)
{

}

void Render(RenderWindow &window) {
	window.draw(invader);
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