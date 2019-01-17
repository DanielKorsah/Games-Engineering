#include <SFML/Graphics.hpp>

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

CircleShape ball;
RectangleShape paddles[2];

Vector2f ballVelocity;
bool server = false;

void Load() 
{
	// Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(770 + paddleSize.x / 2, gameHeight / 2);
	
	reset();
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

	// handle paddle movement
	float direction[2] = {0.0f, 0.0f};
	//left paddle
	if (Keyboard::isKeyPressed(controls[0])) 
	{
		direction[0]--;
	}
	if (Keyboard::isKeyPressed(controls[1])) 
	{
		direction[0]++;
	}
	paddles[0].move(0, direction[0] * paddleSpeed * dt);
	//right paddle
	if (Keyboard::isKeyPressed(controls[2])) 
	{
		direction[1]--;
	}
	if (Keyboard::isKeyPressed(controls[3])) 
	{
		direction[1]++;
	}
	paddles[1].move(0, direction[1] * paddleSpeed * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) {
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
		bx < paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) 
	{
		// bounce off left paddle
	
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

void reset() 
{
	// reset Ball Position
	ball.setPosition(400, 300);
	//if server true 100, if server false -100
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
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