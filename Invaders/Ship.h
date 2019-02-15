#pragma once
#include <SFML/Graphics.hpp>


class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	bool _exploded = false;
	//Default constructor is hidden
	Ship();
public:
	//Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	//Pure virtual deconstructor -- makes this an abstract class
	virtual ~Ship() = 0;
	//Update, virtual so can be overrided, but not pure virtual
	virtual void Update(const float &dt);

	bool isExploded() const { return _exploded; }
	virtual void Explode();
};

class Invader : public Ship {
public:
	//constructors
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();

	static bool direction;
	static float speed;

	void Update(const float &dt) override;
};

class Player : public Ship
{
public:
	Player();
	void Update(const float&dt) override;
};