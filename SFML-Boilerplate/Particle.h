#include <SFML/Graphics.hpp>
#include <string>

class Particle : public sf::Drawable, public sf::Transformable
{
public:
	//Vars
	sf::Texture texture;
	sf::Transform transform;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Time lifetime;

	//Color
	sf::Uint8 red;
	sf::Uint8 green;
	sf::Uint8 blue;
	sf::Uint8 alpha;

	sf::Vector2f velocity;
	std::vector<sf::VertexArray> history;
	int historySteps;
	float historyInterval;

	bool hasGravity;
	bool isDead;

	//Functions
	Particle() {};
	Particle(sf::Vector2f _origin, sf::Vector2f _size, sf::Color _color, std::string  _texture, bool _hasGravity = false, int lifetime = 3000, int _historySteps = 0);
	void MoveTo(sf::Vector2f newPosition);
	void MoveBy(float x, float y);
	void AddVelocity(float x, float y);
	void Update(sf::Time elapsed);
	~Particle();
private:
	//Vars
	sf::VertexArray vertices;
	sf::Vector2f textureSize;

	//Functions
	void SetVertices();
	void SetColor();
	void SetTexture();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};