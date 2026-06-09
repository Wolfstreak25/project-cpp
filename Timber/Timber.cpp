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
        // ========================================



        // ========================================
        // Render
        // ========================================

        window.clear();

        window.draw(background);

        window.display();
    }

    std::cout << "[LOG] Application exiting." << std::endl;

    return 0;
}