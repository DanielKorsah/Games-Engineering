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

int aiMode = 2;

//scoreboard varibales
sf::Font font;
sf::Text text;
int score1 = 0;
int score2 = 0;

CircleShape ball;
RectangleShape paddles[2];

Vector2f ballVelocity;
bool server = true;

void reset(Vector2f location, sf::RenderWindow &w)
{
	// reset Ball Position
	ball.setPosition(location);
	//if server true 100, if server false -100
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	// Update Score Text
	text.setString(std::to_string(score1) + " : " + std::to_string(score2));
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), gameHeight - 30);

	text.setColor(sf::Color::White);
	text.setFillColor(sf::Color::White);

	w.draw(text);
}

void Load(sf::RenderWindow &w) 
{
	// Load font-face from res dir
	font.loadFromFile("res/RobotoMono-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);

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
	
	reset({400, 300}, w);
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
	Vector2f offset = { 10, 10 };
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
		reset({(paddles[0].getPosition().x - offset.x), (paddles[0].getPosition().y)}, window);
	}
	else if (bx < 0)
	{
		// left wall
		reset({ (paddles[1].getPosition().x + offset.x), (paddles[1].getPosition().y)}, window);
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
	Load(window);
	while (window.isOpen()) 
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}