#include "bullet.h"
#include "game.h"
#include <iostream>
using namespace sf;
using namespace std;


Bullet::Bullet() {
};

unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];

void Bullet::Fire(const sf::Vector2f &pos, const bool mode)
{
	//set the next bullet to be fired from the pool to he location of the player
	bullets[bulletPointer].setPosition(pos);
	
	//if invader bullet (mode == true) set green sqiggle, if player bullet (mode == false) set
	if (mode) 
	{
		IntRect sprite = IntRect(108, 40, 7, 15);
		bullets[bulletPointer].setTexture(spritesheet);
		bullets[bulletPointer].setTextureRect(sprite);
	}
	else
	{
		IntRect sprite = IntRect(77, 40, 5, 15);
		bullets[bulletPointer].setTexture(spritesheet);
		bullets[bulletPointer].setTextureRect(sprite);
		bullets[bulletPointer].setOrigin(2.5f, 7.5f);
	}

	
	bullets[bulletPointer]._mode = mode;

	//set start location of bullet
	bullets[bulletPointer].setPosition(pos);
	bulletPointer++;
};

void Bullet::Render(sf::RenderWindow &window)
{
	for (Bullet &b : bullets)
	{
		window.draw(b);
	}
}

void Bullet::Update(const float &dt)
{
	//call protected update for each individual bullet
	for (Bullet &b : bullets)
	{
		b._Update(dt);
	}
}

void Bullet::_Update(const float &dt) {
	//if not on screen dont update
	if (getPosition().y < -64 || getPosition().y > gameHeight + 64)
	{
		return;
	}
	else
	{
		//minus is up, origin at top left
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));

		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships)
		{
			//player bullets don't collide with player
			if (!_mode && s == player)
			{
				continue;
			}
			//invade bullets can't collide with invaders
			if (_mode && s != player)
			{
				continue;
			}

			
			//if bullet intersecting with target have then "destroy" eachother
			if (!s->isExploded() && s->getGlobalBounds().intersects(boundingBox))
			{
				//explode it
				s->Explode();
				//remove bullet from scree
				setPosition(-100, -100);
				return;

			}
		}
	}
}

void Ship::Explode() 
{
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}