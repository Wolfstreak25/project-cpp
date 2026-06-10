#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
constexpr unsigned int WINDOW_WIDTH = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
constexpr float OFFSCREEN_LEFT = -200.f;
constexpr float OFFSCREEN_RIGHT = WINDOW_WIDTH + 200.f;
struct MovingEntity
{
	
	virtual ~MovingEntity() = default;
protected:
	sf::Sprite sprite;
	float speed = 0.0f;
	bool active = false;

	virtual void Spawn() = 0;
	virtual bool IsOutOfBounds() = 0;
	virtual void Move(float dt) = 0;

public:
	MovingEntity(const sf::Texture& texture) :sprite(texture) {
	}

	void Update(float dt) {
		if (!active) {
			Spawn();
		}
		else {
			// Move the bee
			Move(dt);
			// Has the bee reached the left-hand edge of the screen?
			if (IsOutOfBounds()) {
				active = false;
			}
		}
	}

	const sf::Sprite& GetSprite() const
	{
		return sprite;
	}
};

struct Bee :public MovingEntity {
public:
	Bee(const sf::Texture& texture) :MovingEntity(texture) {
	}
protected:
	void Spawn() override
	{
		float height = (rand() % 500 + 500);
		sprite.setPosition({ OFFSCREEN_RIGHT,height });
		speed = (rand() % 200) + 200;
		active = true;
	}
	bool IsOutOfBounds() override {
		return (sprite.getPosition().x < -100);
	}
	void Move(float dt) override {
		sprite.move({ -speed * dt, 0.f });
	}
};

struct Cloud : public MovingEntity {
private :
	float scaleFactor = 0;
public :
	Cloud(const sf::Texture& texture) :MovingEntity(texture) {
	}
protected:
	void Spawn() override
	{
		float height = (rand() % 450 );
		sprite.setPosition({OFFSCREEN_LEFT,height });
		speed = (rand() % 150 )+50 ;
		active = true;
	}
	bool IsOutOfBounds() override {
		return (sprite.getPosition().x > WINDOW_WIDTH);
	}
	void Move(float dt) override{
		sprite.move({ speed * dt, 0.f });
	}
};

int main()
{
	// Initialization
	std::cout << "[LOG] Application Started" << std::endl;
	srand(static_cast<unsigned>(time(nullptr)));


	sf::RenderWindow window(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Timber!"
	);

	sf::Texture backgroundTexture;

	if (!backgroundTexture.loadFromFile("assets/graphics/background.png"))
	{
		return -1;
	}

	sf::Sprite background(backgroundTexture);
	background.setPosition({ 0.f, 0.f });

	// load tree texture
	sf::Vector2f treePos(810.0f, 0.0f);
	sf::Texture treeTexture;
	if (!treeTexture.loadFromFile("assets/graphics/tree.png")) {
		return -1;
	}
	sf::Sprite treeSprite(treeTexture);
	treeSprite.setPosition(treePos);

	sf::Texture beeTexture;
	if (!beeTexture.loadFromFile("assets/graphics/bee.png")) {
		return -1;
	}
	// load claud sprite
	sf::Texture cloudTexture;
	if (!cloudTexture.loadFromFile("assets/graphics/cloud.png")) {
		return -1;
	}

	Bee bee(beeTexture);
	Cloud cloud1(cloudTexture);
	Cloud cloud2(cloudTexture);
	Cloud cloud3(cloudTexture);
	std::vector<MovingEntity*> entities =
	{
		&bee,
		&cloud1,
		&cloud2,
		&cloud3
	};
	sf::Clock clock;

	// Game Loop
	while (window.isOpen())
	{
		// Event Processing

		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			std::cout << "[INPUT] Escape Pressed" << std::endl;
			window.close();
		}


		// Update
		// Measure time
		const float dt = clock.restart().asSeconds();

		for (auto* entity : entities)
		{
			entity->Update(dt);
		}


		// Render
		window.clear();

		window.draw(background);
		window.draw(treeSprite);
		for (auto* entity : entities)
		{
			window.draw(entity->GetSprite());
		}

		window.display();
	}

	std::cout << "[LOG] Application exiting." << std::endl;

	return 0;
}