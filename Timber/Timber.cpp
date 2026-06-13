#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Utilities/Logger.hpp"
#include "Resources/TextureManager.hpp"
#include "Math/Random.hpp"
#include "Resources/AudioManager.hpp"


constexpr unsigned int WINDOW_WIDTH = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
constexpr unsigned int WINDOW_WIDTH_CENTER = 960;
constexpr unsigned int WINDOW_HEIGHT_CENTER = 540;
constexpr sf::Vector2f WINDOW_CENTER = { WINDOW_WIDTH_CENTER, WINDOW_HEIGHT_CENTER };
constexpr sf::Vector2f WINDOW_CENTER_BOTTOM = { WINDOW_WIDTH_CENTER, WINDOW_HEIGHT };
constexpr float OFFSCREEN_LEFT = -300.f;
constexpr float OFFSCREEN_RIGHT = WINDOW_WIDTH + 200.f;

enum class Side { None, Left, Right };
enum class GameState { PAUSED, PLAYING, GAMEOVER };

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
		sprite.setPosition({ OFFSCREEN_RIGHT,sprite.getPosition().y });
	}
protected:
	void Spawn() override
	{
		float height = (Engine::Random::IntRange(500, 1000));
		sprite.setPosition({ OFFSCREEN_RIGHT,height });
		speed = Engine::Random::IntRange(200, 400);
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
private:
	float scaleFactor = 0;
public:
	Cloud(const sf::Texture& texture) :MovingEntity(texture) {
		sprite.setPosition({ OFFSCREEN_LEFT,sprite.getPosition().y });
	}
protected:
	void Spawn() override
	{
		float height = (Engine::Random::IntRange(0, 450));
		sprite.setPosition({ OFFSCREEN_LEFT,height });
		speed = Engine::Random::IntRange(50, 200);
		active = true;
	}
	bool IsOutOfBounds() override {
		return (sprite.getPosition().x > WINDOW_WIDTH);
	}
	void Move(float dt) override {
		sprite.move({ speed * dt, 0.f });
	}
};

struct Branch {
private:
	Side side = Side::None;
	sf::Sprite sprite;
	float speed = 0.0f;
	int id = 0;

	void SetSide() {
		int rot = (Engine::Random::IntRange(0, 5));
		float height = (150 * id) + 50;
		switch (rot) {
		case 0:
			side = Side::Left;
			sprite.setRotation(sf::degrees(180));
			sprite.setPosition({ 660, height });
			break;
		case 1:
			side = Side::Right;
			sprite.setRotation(sf::degrees(0));
			sprite.setPosition({ 1330, height });
			break;
		default:
			side = Side::None;
			sprite.setPosition({ 3000, height });
		}
	}
public:
	Branch(const sf::Texture& texture, int _id) :sprite(texture) {
		id = _id;
		sf::FloatRect rect = sprite.getLocalBounds();
		sprite.setOrigin(rect.getCenter());
		SetSide();
	}
	void ShiftDown(sf::Vector2f _newPos, Side _side) {
		SetSide(_side);
		sprite.setPosition(_newPos);
	}
	void ShiftDown(sf::Vector2f pos) {
		SetSide();
		sprite.setPosition({ sprite.getPosition().x,pos.y });
	}

	const sf::Sprite& GetSprite() const
	{
		return sprite;
	}

	const Side GetSide() const
	{
		return side;
	}

	void SetSide(Side s)
	{
		side = s;
		float height = (150 * id) + 50;

		if (side == Side::Left)
		{
			sprite.setPosition({ 660, height });
			sprite.setRotation(sf::degrees(180));
		}
		else if (side == Side::Right)
		{
			sprite.setPosition({ 1330, height });
			sprite.setRotation(sf::degrees(0));
		}
		else
		{
			sprite.setPosition({ 3000, height });
		}
	}

	void ResetBranch() {
		side = Side::None;
		float height = (150 * id) + 50;
		sprite.setPosition({ 3000, height });
	}
	void SetBranch() {
		SetSide();
	}
};

void SetMessageTextLabel(sf::Text& messageText, std::string text, sf::Color color) {
	sf::FloatRect textRect = messageText.getLocalBounds();
	messageText.setString(text);
	messageText.setFillColor(color);
	textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.getCenter());
	messageText.setPosition(WINDOW_CENTER);
}

void UpdateTimeBar(sf::RectangleShape& timeBar, sf::Vector2f size) {
	timeBar.setSize(size);
	sf::FloatRect timeBarRect = timeBar.getLocalBounds();
	timeBar.setOrigin(timeBarRect.getCenter());
	timeBar.setPosition({ WINDOW_WIDTH_CENTER, WINDOW_HEIGHT - (timeBar.getSize().y + 5) });
}

float UpdateFPS(float dt) {
	static float timeAccumulator = 0.0f;
	static int frameCount = 0;
	static float currentFPS = 0.0f;

	timeAccumulator += dt;
	frameCount++;
	if (timeAccumulator >= 1.0f) {
		currentFPS = static_cast<float>(frameCount) / timeAccumulator;
		timeAccumulator -= 1.0f;
		frameCount = 0;
	}
	return currentFPS;
}

void UpdateBranch(std::vector<std::unique_ptr<Branch>>& branches) {

	std::vector<Side> oldSides;
	for (auto& branch : branches) {
		oldSides.push_back(branch->GetSide());
	}

	// Shift sides DOWN: each branch takes the side of the one ABOVE it
	for (int i = static_cast<int>(branches.size()) - 1; i > 0; i--) {
		branches[i]->SetSide(oldSides[i - 1]);
	}

	// Top branch (index 0) gets a new random side
	branches[0]->SetBranch();
}

int main()
{
	// Initialization
	//std::cout << "[LOG] Application Started" << std::endl;
	Engine::TextureManager textureManager;
	Engine::AudioManager audioManager;
	bool acceptInput = false;
	Engine::Logger::Error("Application Started", "false");
	int score = 0;
	GameState currentState = GameState::PAUSED;
	srand(static_cast<unsigned>(time(nullptr)));

	sf::RenderWindow window(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Timber!"
	);

	//sf::Texture backgroundTexture;

	if (!textureManager.Load("assets/graphics/background.png"))
	{
		return -1;
	}

	sf::Sprite background(textureManager.Get("assets/graphics/background.png"));
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
	sf::Texture branchTexture;
	if (!branchTexture.loadFromFile("assets/graphics/branch.png")) {
		return -1;
	}

	std::vector<std::unique_ptr<MovingEntity>> entities;

	// Bee
	entities.emplace_back(std::make_unique<Bee>(beeTexture));

	// Clouds
	entities.emplace_back(std::make_unique<Cloud>(cloudTexture));
	entities.emplace_back(std::make_unique<Cloud>(cloudTexture));
	entities.emplace_back(std::make_unique<Cloud>(cloudTexture));

	// Branches
	std::vector<std::unique_ptr<Branch>> branches;
	const int NUM_BRANCHES = 6;
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches.emplace_back(std::make_unique<Branch>(branchTexture, i));
	}
	std::cout << "Branches : " << branches.size() << std::endl;

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/graphics/player.png")) {
		return -1;
	}
	sf::Sprite playerSprite(playerTexture);
	Side playerSide = Side::Left;
	playerSprite.setPosition({ 580, 720 });

	sf::Texture logTexture;
	if (!logTexture.loadFromFile("assets/graphics/log.png")) {
		return -1;
	}
	sf::Sprite logSprite(logTexture);
	float logSpeedX = 1000.0f;
	float logSpeedY = -1500.0f;
	bool isLogActive = false;

	sf::Texture ripTexture;
	if (!ripTexture.loadFromFile("assets/graphics/rip.png")) {
		return -1;
	}
	sf::Sprite ripSprite(ripTexture);
	ripSprite.setPosition({ 600, 860 });

	sf::Texture axeTexture;
	if (!axeTexture.loadFromFile("assets/graphics/axe.png")) {
		return -1;
	}
	sf::Sprite axeSprite(axeTexture);
	axeSprite.setPosition({ 700, 830 });
	const float AXE_POS_LEFT = 700.0f;
	const float AXE_POS_RIGHT = 1075.0f;

	audioManager.LoadSound("assets/sound/chop.wav");
	audioManager.LoadSound("assets/sound/death.wav");
	audioManager.LoadSound("assets/sound/out_of_time.wav");


	sf::Clock clock;
	sf::RectangleShape timeBar;
	float timeBarStartwidth = 400.0f;
	float timeBarHeight = 80.0f;
	timeBar.setFillColor(sf::Color::Red);
	UpdateTimeBar(timeBar, { timeBarStartwidth, timeBarHeight });

	sf::Time gameTimeTotal;
	float timeRemaining = 2006.0f;
	float timeBarwidthPerSecond = timeBarStartwidth / timeRemaining;

	sf::Font font;
	if (!font.openFromFile("assets/fonts/KOMIKAP_.ttf")) {
		return -1;
	}
	sf::Text scoreText(font, "Score : " + score, 30);
	sf::Text fpsText(font, "FPS : 000", 30);
	sf::Text messageText(font, "Press [ ENTER ] to start", 50);
	SetMessageTextLabel(messageText, "Press [ ENTER ] to start", (sf::Color::White));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition({ 20, 20 });
	fpsText.setPosition({ 20, 60 });

	// Game Loop
	while (window.isOpen())
	{
		// Event Processing

		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::KeyReleased>() && (currentState == GameState::PLAYING)) {
				acceptInput = true;
				axeSprite.setPosition({ 2000, axeSprite.getPosition().y });
			}
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		if (acceptInput && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			acceptInput = false;
			std::cout << "[INPUT] Escape Pressed" << std::endl;
			if (currentState != GameState::PLAYING) {
				currentState = GameState::GAMEOVER;
				window.close();
			}
			else {
				currentState = GameState::PAUSED;
				SetMessageTextLabel(messageText, "PAUSED!", (sf::Color::Yellow));
			}
		}
		// Start the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && currentState != GameState::PLAYING)
		{
			currentState = GameState::PLAYING;
			// Reset the time and the score
			std::cout
				<< "Bottom branch = "
				<< (int)branches.back()->GetSide()
				<< std::endl;
			score = 0;
			timeRemaining = 6;
			timeBarwidthPerSecond = timeBarStartwidth / timeRemaining;
			ripSprite.setPosition({ ripSprite.getPosition().x, 2000 });
			acceptInput = true;
			playerSide = Side::Left;
			playerSprite.setPosition({ 580, 660 });
			axeSprite.setPosition({ 700, 830 });

			for (auto& branch : branches) {
				branch->ResetBranch();
			}
		}

		if (acceptInput && currentState == GameState::PLAYING) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
				playerSide = Side::Right;
				axeSprite.setPosition({ AXE_POS_RIGHT, axeSprite.getPosition().y });
				playerSprite.setPosition({ 1200,720 });

				audioManager.PlaySound("assets/sound/chop.wav");
				score++;
				timeRemaining += (2.0f / score) + 0.15f;

				UpdateBranch(branches);

				if (branches.back()->GetSide() == playerSide)
				{
					currentState = GameState::GAMEOVER;
					SetMessageTextLabel(messageText,
						"SQUISHED!!",
						sf::Color::Red);

					ripSprite.setPosition(playerSprite.getPosition());
					playerSprite.setPosition({ 2000,660 });
					audioManager.PlaySound("assets/sound/death.wav");
				}

				logSprite.setPosition({ 810,720 });
				logSpeedX = -5000;
				isLogActive = true;
				acceptInput = false;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
				audioManager.PlaySound("assets/sound/chop.wav");

				playerSide = Side::Left;
				score++;
				timeRemaining += (2.0f / score) + 0.15f;
				axeSprite.setPosition({ AXE_POS_LEFT, axeSprite.getPosition().y });
				playerSprite.setPosition({ 580,720 });

				UpdateBranch(branches);

				if (branches.back()->GetSide() == playerSide)
				{
					currentState = GameState::GAMEOVER;
					SetMessageTextLabel(messageText,
						"SQUISHED!!",
						sf::Color::Red);

					ripSprite.setPosition(playerSprite.getPosition());
					playerSprite.setPosition({ 2000,660 });
					audioManager.PlaySound("assets/sound/death.wav");
				}

				logSprite.setPosition({ 810,720 });
				logSpeedX = 5000;
				isLogActive = true;
				acceptInput = false;
			}
		}


		if (currentState == GameState::PLAYING) {
			// Update
			// Measure time
			const float dt = clock.restart().asSeconds();
			timeRemaining -= dt;
			UpdateTimeBar(timeBar, { timeBarwidthPerSecond * timeRemaining, timeBarHeight });
			if (isLogActive) {
				logSprite.setPosition({ logSprite.getPosition().x + (logSpeedX * dt),logSprite.getPosition().y + (logSpeedY * dt) });
				if (logSprite.getPosition().x < -100 || logSprite.getPosition().x > 2000) {
					isLogActive = false;
					logSprite.setPosition({ 810,720 });
				}
			}

			UpdateTimeBar(timeBar, { timeBarwidthPerSecond * timeRemaining, timeBarHeight });
			if (timeRemaining <= 0.0f) {
				currentState = GameState::GAMEOVER;
				audioManager.PlaySound("assets/sound/out_of_time.wav");
				SetMessageTextLabel(messageText, "Out Of Time !", sf::Color::Red);
			}
			for (auto& entity : entities)
			{
				entity->Update(dt);
			}

			std::stringstream ss;
			ss << "Score : " << score;
			scoreText.setString(ss.str());
			std::stringstream sfps;
			sfps << "FPS : " << UpdateFPS(dt);
			fpsText.setString(sfps.str());
		}
		else {
			clock.restart();
		}
		// Render
		window.clear();

		window.draw(background);
		window.draw(treeSprite);
		for (auto& entity : entities)
		{
			window.draw(entity->GetSprite());
		}
		for (auto& branch : branches)
		{
			window.draw(branch->GetSprite());
		}
		window.draw(scoreText);
		if (currentState != GameState::PLAYING)
		{
			// Draw our message
			window.draw(messageText);
		}
		window.draw(playerSprite);
		window.draw(axeSprite);
		if (currentState == GameState::GAMEOVER) {
			window.draw(ripSprite);
		}
		window.draw(logSprite);
		window.draw(timeBar);
		window.draw(fpsText);

		window.display();
	}

	std::cout << "[LOG] Application exiting." << std::endl;

	return 0;
}