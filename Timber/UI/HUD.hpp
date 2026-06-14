#pragma once
#include <SFML/Graphics.hpp>
#include <string>
namespace Timber {
	class HUD
	{
	public:
		HUD(sf::Font font);

		void SetScore(int score);
		void SetFPS(float fps);
		void SetMessage(const std::string& text, sf::Color color);
		void HideMessage();
		void Draw(sf::RenderWindow& window, bool showMessage) const;
	private:
		sf::Text m_scoreText;
		sf::Text m_fpsText;
		sf::Text m_messageText;
		bool m_showMessage;
	};
}