#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(unsigned int count, int _size, sf::Color _color, std::string _texture, bool _hasGravity, bool _fade, sf::Vector2f particleSize, int _speedRange, float _speedBase, int _angleRange, int _angleBase, int _timeRange, int _timeBase): particles(count), lifetime(sf::seconds(3)), emitter(0, 0)
{
	size = _size;
	color = _color;
	hasGravity = _hasGravity;
	fade = _fade;
	pSize = particleSize;
	speedBase = _speedBase;
	speedRange = _speedRange;
	angleBase = _angleBase;
	angleRange = _angleRange;
	timeBase = _timeBase;
	timeRange = _timeRange;
	texture = _texture;

	for (int i = 0; i < count; i++)
	{
		particles[i] = Particle(sf::Vector2f((std::rand() % size) - size * 0.5f + emitter.x, emitter.y), pSize, color, texture, hasGravity, lifetime.asMilliseconds());
	}
}


ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::SetEmitter(sf::Vector2f position)
{
	emitter = position;
}

void ParticleEmitter::IncreaseParticles()
{
	particles.push_back(Particle(sf::Vector2f((std::rand() % size) - size * 0.5f + emitter.x, emitter.y), pSize, color, texture, hasGravity, lifetime.asMilliseconds()));
	ResetParticle(particles.size() - 1);
}

void ParticleEmitter::DecreaseParticles()
{
	if(particles.size() > 2)
		particles.pop_back();
}

void ParticleEmitter::ResetParticle(std::size_t index)
{
	// give a random velocity and lifetime to the particle
	float angle = ((std::rand() % angleRange) + angleBase) * 3.14f / 180.f;
	float speed = (std::rand() % speedRange) + speedBase;
	particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	particles[index].lifetime = sf::milliseconds((std::rand() % timeRange) + timeBase);

	// reset the position of the corresponding vertex
	particles[index].position = sf::Vector2f((std::rand() % size) - size * 0.5f + emitter.x, emitter.y);
	particles[index].isDead = false;
}

void ParticleEmitter::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	//target.draw(m_vertices, states);
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		const Particle &p = particles[i];
		target.draw(p, states);
	}

}

void ParticleEmitter::update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		Particle &p = particles[i];
		float transparencyRatio = p.lifetime.asSeconds()/ lifetime.asSeconds();
		if(fade) p.alpha = static_cast<sf::Uint8>(transparencyRatio * 255);
		if (p.hasGravity)
		{
			p.velocity.y += gravity;
		}
		p.Update(elapsed);
		if (p.isDead)
		{
			ResetParticle(i);
		}
	}
}
