#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>
#include "ParticleEmitter.h"
int main();
//functions;
void update();

sf::RenderWindow *window;
bool hasGravity;
sf::VertexArray quad;
sf::RenderStates quadStates;
sf::Transform quadTransform;
int particleOriginX = 0;
int particleOriginY = 500;
int particleWidth = 100;
int particleHeight = 100;
float gravity = 0.1f;
//size, range.
ParticleEmitter emitter(200, 60, sf::Color::Color(255, 100, 0, 200), "fire.png", false, true, sf::Vector2f(20, 20), 400, 400, 20, 260, 200, 600);
ParticleEmitter emitter0(200, 50, sf::Color::White, "fire.png", false, true, sf::Vector2f(20, 20), 400, 400, 20, 260, 200, 400);
ParticleEmitter emitter1(200, 25, sf::Color::White, "fire_blue.png", false, true, sf::Vector2f(20, 20), 400, 400, 20, 260, 100, 200);
ParticleEmitter emitter2(100, 100, sf::Color::Color(255, 125, 0, 255), "", true, false , sf::Vector2f(1, 1), 100,150, 360, 0, 400, 200);
ParticleEmitter emitter3(100, 100, sf::Color::Color(255, 255, 255, 125), "cloud.png", false, true, sf::Vector2f(30, 30), 25, 25, 45, 270, 1000, 500);
ParticleEmitter emitter4(100, 1920, sf::Color::White, "drop.png", true, false, sf::Vector2f(4, 8), 200, 200, 45, 90);

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "PGC - Spaceship Exhaust & Rain");
	
	update();

	return 0;
}

void update()
{
	sf::Clock clock;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			emitter.IncreaseParticles();
			emitter.IncreaseParticles();
			emitter0.IncreaseParticles();
			emitter0.IncreaseParticles();
			emitter1.IncreaseParticles();
			emitter1.IncreaseParticles();
			emitter2.IncreaseParticles();
			emitter3.IncreaseParticles();
			emitter4.IncreaseParticles();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			emitter.DecreaseParticles();
			emitter0.DecreaseParticles();
			emitter1.DecreaseParticles();
			emitter2.DecreaseParticles();
			emitter3.DecreaseParticles();
			emitter4.DecreaseParticles();
		}

		window->clear();
		//Draw quad vertex array with texture.
		sf::Vector2i mouse = sf::Mouse::getPosition(*window);
		emitter.SetEmitter(window->mapPixelToCoords(mouse));
		emitter0.SetEmitter(window->mapPixelToCoords(mouse));
		emitter1.SetEmitter(window->mapPixelToCoords(mouse));
		emitter2.SetEmitter(window->mapPixelToCoords(mouse));
		emitter3.SetEmitter(window->mapPixelToCoords(mouse));
		emitter4.setPosition(960, 0);
		sf::Time elapsed = clock.restart();
		emitter.update(elapsed);
		emitter0.update(elapsed);
		emitter1.update(elapsed);
		emitter2.update(elapsed);
		emitter3.update(elapsed);
		emitter4.update(elapsed);
		window->draw(emitter);
		window->draw(emitter0);
		window->draw(emitter1);
		window->draw(emitter2);
		window->draw(emitter3);
		window->draw(emitter4);
		window->display();
	}
}
