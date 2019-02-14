#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet::Bullet(const sf::Vector2f &pos, const bool mode)
{
	//if invader bullet (mode == true) set green sqiggle, if player bullet (mode == false) set
	if (mode) 
	{
		IntRect sprite = IntRect(108, 40, 7, 15);
		setTexture(spritesheet);
		setTextureRect(sprite);
	}
	else
	{
		IntRect sprite = IntRect(77, 40, 5, 15);
		setTexture(spritesheet);
		setTextureRect(sprite);
		setOrigin(2.5f, 7.5f);
	}

	//set start location of bullet
	setPosition(pos);
};

void Bullet::Update(const float &dt) {
	move(0, dt * 200.0f * (_mode ? -1.0f : 1.0f));
}