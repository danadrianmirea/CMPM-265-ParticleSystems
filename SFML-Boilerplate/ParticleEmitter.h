#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "Particle.h"

class ParticleEmitter : public sf::Drawable, public sf::Transformable
{
public:
	ParticleEmitter(unsigned int count, int _size, sf::Color _color, std::string texture, bool _hasGravity, bool _fade, sf::Vector2f particleSize, int _speedRange = 100, float _speedBase = 50, int _angleRange = 360, int _angleBase = 0, int _timeRange = 2000, int _timeBase = 1000);
	~ParticleEmitter();
	void SetEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);
	int angleRange;
	int angleBase;
	int timeRange;
	int timeBase;
	int speedRange;
	float speedBase;
	bool hasGravity;
	bool fade;
	sf::Vector2f pSize;
	sf::Color color;
	float gravity = 1;
	void IncreaseParticles();
	void DecreaseParticles();
	std::string texture;
private:
	std::vector<Particle> particles;
	sf::Time lifetime;
	sf::Vector2f emitter;
	int size;
	void ResetParticle(std::size_t index);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

