#include <SFML/Graphics.hpp>
/*  sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-network-d.lib;sfml-audio-d.lib;
*/
int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 1920, 1080 }),
        "Timber!"
    );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}