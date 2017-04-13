#include "Particle.h"



Particle::Particle(sf::Vector2f _origin, sf::Vector2f _size, sf::Color _color, std::string  _texture, bool _hasGravity, int _lifetime, int _historySteps)
{
	position = _origin;
	size = _size;
	vertices = sf::VertexArray(sf::Quads, 4);
	SetVertices();

	red = _color.r;
	blue = _color.b;
	green = _color.g;
	alpha = _color.a;

	SetColor();

	texture.loadFromFile(_texture);
	SetTexture();

	hasGravity = _hasGravity;

	lifetime = sf::milliseconds(_lifetime);

	historySteps = _historySteps;
	historyInterval = 0.25;

	isDead = false;
}


Particle::~Particle()
{
}

void Particle::SetVertices()
{
	vertices[0].position = sf::Vector2f(position.x, position.y);
	vertices[1].position = sf::Vector2f(position.x + size.x, position.y);
	vertices[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
	vertices[3].position = sf::Vector2f(position.x, position.y + size.y);

}
void Particle::SetColor()
{
	vertices[0].color = sf::Color::Color(red, green, blue, alpha);
	vertices[1].color = sf::Color::Color(red, green, blue, alpha);
	vertices[2].color = sf::Color::Color(red, green, blue, alpha);
	vertices[3].color = sf::Color::Color(red, green, blue, alpha);
}

void Particle::SetTexture()
{
	textureSize.x = texture.getSize().x;
	textureSize.y = texture.getSize().y;

	vertices[0].texCoords = sf::Vector2f(0, 0);
	vertices[1].texCoords = sf::Vector2f(textureSize.x, 0);
	vertices[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
	vertices[3].texCoords = sf::Vector2f(0, textureSize.y);
}

void Particle::MoveTo(sf::Vector2f newPosition)
{
	position = newPosition;
	SetVertices();
}

void Particle::MoveBy(float x, float y)
{
	position.x = position.x + x;
	position.y = position.y + y;
	SetVertices();
}

void Particle::AddVelocity(float x, float y)
{
	velocity.x += x;
	velocity.y += y;
}

void Particle::Update(sf::Time elapsed)
{
	SetColor();
	MoveBy(velocity.x * elapsed.asSeconds(), velocity.y * elapsed.asSeconds());
	lifetime -= elapsed;

	if (lifetime <= sf::Time::Zero)
		isDead = true;


}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
										// apply the texture
	states.texture = &texture;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(vertices, states);
}