#include "HUD.hpp"
#include "Config/Constants.hpp"
#include <sstream>

namespace Timber {
	HUD::HUD(const sf::Font& font)
		:m_scoreText(font, "Score : 0", 30)
		, m_fpsText(font, "FPS : 0", 30)
		, m_messageText(font, "Press [ ENTER ] to start", 50)
		, m_showMessage(true) {
		m_scoreText.setFillColor(sf::Color::White);
		m_scoreText.setPosition({ 20,20 });
		m_fpsText.setPosition({ 20,60 });

		SetMessage("Press [ ENTER ] to start", sf::Color::White);
	}

	void HUD::SetScore(int score) {
		std::stringstream ss;
		ss << "Score : " << score;
		m_scoreText.setString(ss.str());
	}

	void HUD::SetFPS(float fps) {
		std::stringstream ss;
		ss << "FPS : " << fps;
		m_fpsText.setString(ss.str());
	}

	void HUD::SetMessage(const std::string& text, sf::Color color) {
		m_messageText.setString(text);
		m_messageText.setFillColor(color);
		sf::FloatRect textRect = m_messageText.getLocalBounds();
		m_messageText.setOrigin(textRect.getCenter());
		m_messageText.setPosition(WINDOW_CENTER);
		m_showMessage = true;
	}

	void HUD::HideMessage() {
		m_showMessage = false;
	}

	void HUD::Draw(sf::RenderWindow& window, bool showMessage) const {
		window.draw(m_scoreText);
		window.draw(m_fpsText);
		if (showMessage && m_showMessage) {
			window.draw(m_messageText);
		}
	}
}