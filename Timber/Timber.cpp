#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	// ========================================
	// Initialization
	// ========================================

	constexpr unsigned int WINDOW_WIDTH = 1920;
	constexpr unsigned int WINDOW_HEIGHT = 1080;



	std::cout << "[LOG] Creating window..." << std::endl;

	sf::RenderWindow window(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Timber!"
	);

	std::cout << "[LOG] Window created successfully." << std::endl;

	sf::Texture backgroundTexture;

	if (!backgroundTexture.loadFromFile("assets/graphics/background.png"))
	{
		std::cerr << "[ERROR] Failed to load: assets/graphics/background.png" << std::endl;
		return -1;
	}

	std::cout << "[LOG] Background texture loaded." << std::endl;

	sf::Sprite background(backgroundTexture);
	background.setPosition({ 0.f, 0.f });

	// load tree texture
	sf::Vector2f treePos(810.0f, 0.0f);
	sf::Texture treeTexture;
	if (!treeTexture.loadFromFile("assets/graphics/tree.png")) {
		std::cerr << "[ERROR] Failed to load: assets/graphics/tree.png" << std::endl;
	}
	std::cout << "[LOG] Tree texture loaded." << std::endl;
	sf::Sprite treeSprite(treeTexture);
	treeSprite.setPosition(treePos);

	// load bee sprite
	sf::Vector2f beePos(0.0f, 800.0f);
	bool beeActive = false;
	float beeSpeed = 0.0f;
	sf::Texture beeTexture;
	if (!beeTexture.loadFromFile("assets/graphics/bee.png")) {
		std::cerr << "[ERROR] Failed to load: assets/graphics/bee.png" << std::endl;
	}
	std::cout << "[LOG] Tree texture loaded." << std::endl;
	sf::Sprite beeSprite(beeTexture);
	beeSprite.setPosition(beePos);

	// load claud sprite

	sf::Vector2f cloudPos1(0.0f, 250.0f);
	sf::Vector2f cloudPos2(0.0f, 0.0f);
	sf::Vector2f cloudPos3(0.0f, 500.0f);
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	float cloud1Speed = 0;
	float cloud2Speed = 0;
	float cloud3Speed = 0;
	sf::Texture cloudTexture;
	if (!cloudTexture.loadFromFile("assets/graphics/cloud.png")) {
		std::cerr << "[ERROR] Failed to load: assets/graphics/cloud.png" << std::endl;
	}
	std::cout << "[LOG] Tree texture loaded." << std::endl;
	sf::Sprite cloudSprite1(cloudTexture);
	sf::Sprite cloudSprite2(cloudTexture);
	sf::Sprite cloudSprite3(cloudTexture);
	cloudSprite1.setPosition(cloudPos1);
	cloudSprite2.setPosition(cloudPos2);
	cloudSprite3.setPosition(cloudPos3);

	sf::Clock clock;
	// ========================================
	// Game Loop
	// ========================================

	while (window.isOpen())
	{
		// ========================================
		// Event Processing
		// ========================================

		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				std::cout << "[EVENT] Window Closed" << std::endl;
				window.close();
			}

			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				std::cout
					<< "[EVENT] Key Pressed: "
					<< static_cast<int>(keyPressed->code)
					<< std::endl;
			}
		}

		// ========================================
		// Real-Time Input
		// ========================================

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			std::cout << "[INPUT] Escape Pressed" << std::endl;
			window.close();
		}

		// ========================================
		// Update
		// Measure time
		sf::Time dt = clock.restart();
		// ========================================

		// setup the bee
		if (!beeActive) {
			// how fast is bee
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			// how high is bee
			srand((int)time(0) * 10);
			float height = (rand() % 500 + 500);
			beeSprite.setPosition({ 2000,height });
			beeActive = true;
		}
		else {
			// Move the bee
			beeSprite.setPosition({ beeSprite.getPosition().x - (beeSpeed * dt.asSeconds()), beeSprite.getPosition().y });
			// Has the bee reached the left-hand edge of the screen?
			if (beeSprite.getPosition().x < -100) {
				// Set it up ready to be a whole new bee next frame
				beeActive = false;
			}
		}

		// manage the clouds

		if (!cloud1Active)
		{
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);
			// cloude height
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			cloudSprite1.setPosition({ -200, height });
			cloud1Active = true;
		}
		else {
			cloudSprite1.setPosition(
				{
					cloudSprite1.getPosition().x + (cloud1Speed * dt.asSeconds()),
				cloudSprite1.getPosition().y }
				);
			// check edge
			if (cloudSprite1.getPosition().x > 1920) {
				cloud1Active = false;
			}
		}

		if (!cloud2Active) {
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 250);
			// cloude height
			srand((int)time(0) * 20);
			float height = (rand() % 200);
			cloudSprite2.setPosition({ -250, height });
			cloud2Active = true;

		}
		else {
			cloudSprite2.setPosition(
				{
					cloudSprite2.getPosition().x + (cloud2Speed * dt.asSeconds()),
					cloudSprite2.getPosition().y
				});

			if (cloudSprite2.getPosition().x > 1920) {
				cloud2Active = false;
			}
		}

		if (!cloud3Active)
		{
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 150);
			// cloude height
			srand((int)time(0) * 30);
			float height = (rand() % 300);
			cloudSprite3.setPosition({ -200, height });
			cloud3Active = true;
		}
		else {
			cloudSprite3.setPosition(
				{
					cloudSprite3.getPosition().x + (cloud3Speed * dt.asSeconds()),
				cloudSprite3.getPosition().y }
				);
			// check edge
			if (cloudSprite3.getPosition().x > 1920) {
				cloud3Active = false;
			}
		}

		// ========================================
		// Render
		// ========================================

		window.clear();

		window.draw(background);
		window.draw(treeSprite);
		window.draw(beeSprite);
		window.draw(cloudSprite1);
		window.draw(cloudSprite2);
		window.draw(cloudSprite3);

		window.display();
	}

	std::cout << "[LOG] Application exiting." << std::endl;

	return 0;
}