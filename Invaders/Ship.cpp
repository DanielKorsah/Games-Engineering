#include "ship.h"
#include "game.h"
#include <typeinfo>
#include "bullet.h"
using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;


Invader::Invader() : Ship() {}

bool Invader::direction = true;
float Invader::speed = 50;

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) 
{
	setOrigin(15.5, 15.5);
	setPosition(pos);
}

void Invader::Update(const float &dt) 
{
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16))
	{
		speed *= 1.1f;
		direction = !direction;
		//skip the last inex as that's where the player is
		for (int i = 0; i < ships.size() -1; i++)
		{
				ships[i]->move(0, 24);
		}
	}

	//randomly fire, no quicker than 4 seconds apart, no faster than 30 seconds apart
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && rand() % 100 == 0) 
	{
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 30);
	}
}

Player::Player() : Ship(IntRect(160, 32, 32, 32))
{
	setPosition({ gameHeight * 0.5f, gameHeight - 32.0f });
	setOrigin(16, 16);

}

void Player::Update(const float &dt)
{
	Ship::Update(dt);

	float playerSpeed = 120.0f;
	//move left
	if (Keyboard::isKeyPressed(Keyboard::A))
		move(dt * -playerSpeed, 0);
	//move right
	if (Keyboard::isKeyPressed(Keyboard::D))
		move(dt * playerSpeed, 0);

	//fire timer
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) 
	{
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
}
