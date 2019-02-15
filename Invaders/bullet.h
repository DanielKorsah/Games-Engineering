#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	//updates All bullets
	static void Update(const float &dt);
	//Render's All bullets
	static void Render(sf::RenderWindow &window);
	//Chose an inactive bullet and use it.
	static void Fire(const sf::Vector2f &pos, const bool mode);


	~Bullet() = default;
protected:
	static unsigned char bulletPointer;
	static Bullet bullets[256];

	//called by the static update
	void _Update(const float &dt);


	//never called by my code
	Bullet();
	//false=player bullet, true=Enemy bullet
	bool _mode;
	
};