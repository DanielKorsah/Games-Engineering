#include <SFML/Graphics.hpp>
#include "main.h"

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

int aiMode = 1;

CircleShape ball;
RectangleShape paddles[2];

Vector2f ballVelocity;
bool server = false;

void reset()
{
	// reset Ball Position
	ball.setPosition(400, 300);
	//if server true 100, if server false -100
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void Load() 
{
	// Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}

	//set player colours
	paddles[0].setFillColor(sf::Color::Red);
	paddles[1].setFillColor(sf::Color::Blue);

	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(770 + paddleSize.x / 2, gameHeight / 2);
	
	reset();
}

void Player1(float dt)
{
	// handle paddle movement
	float direction = 0.0f;
	//left paddle
	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}
	paddles[0].move(0, direction * paddleSpeed * dt);
}

void Player2(float dt)
{
	float direction = 0.0f;

	//right paddle
	if (Keyboard::isKeyPressed(controls[2]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[3]))
	{
		direction++;
	}
	paddles[1].move(0, direction * paddleSpeed * dt);
}

void AI(sf::RectangleShape &paddle, float dt)
{
	float direction = 0.0f;

	if (ball.getPosition().y < paddle.getPosition().y)
	{
		direction--;
	}

	if (ball.getPosition().y > paddle.getPosition().y)
	{
		direction++;
	}
	paddle.move(0, direction * paddleSpeed * dt);
}

void ValidateMoves()
{
	for (auto &p : paddles)
	{
		if (p.getPosition().y + (paddleSize.y * 0.5f) > gameHeight)
		{
			p.setPosition(p.getPosition().x, gameHeight - paddleSize.y * 0.5f);
			//p.setFillColor(sf::Color::Green);
		}
		else if (p.getPosition().y - (paddleSize.y * 0.5f) < 0)
		{
			p.setPosition(p.getPosition().x, 0 + paddleSize.y * 0.5f);
			//p.setFillColor(sf::Color::Red);
		}
		else
		{
			//p.setFillColor(sf::Color::White);
		}
	}
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

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	
	if (aiMode == 0)
	{
		Player1(dt);
		Player2(dt);
	}
	else if (aiMode == 1)
	{
		Player1(dt);
		AI(paddles[1], dt);
	}
	else if (aiMode == 2)
	{
		AI(paddles[0], dt);
		AI(paddles[1], dt);
	}
	

	//validate paddle moves
	ValidateMoves();

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) 
	{
	  // bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) 
	{
		// top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) 
	{
		// right wall
		reset();
	}
	else if (bx < 0)
	{
		// left wall
		reset();
	}
	else if (
		//ball is inline or behind paddle
		bx < paddles[0].getPosition().x + (paddleSize.x * 0.5) &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) 
	{
		// bounce off left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(10, 0);
	}
	else if (
		//ball is inline or behind paddle
		bx > paddles[1].getPosition().x - (paddleSize.x * 0.5) &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) 
	{
		//bounce off riught paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);

	}


	//translate ball position
	ball.move(ballVelocity * dt);
}

void Render(RenderWindow &window) 
{
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
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
	return 0;
}