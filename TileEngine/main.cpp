#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

using namespace sf;

void Load()
{

}

void Update(RenderWindow &window)
{

	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

}

void Render(RenderWindow &w)
{

}


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "TileEngine");

	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;
}