#include "TimeBar.hpp"
namespace Timber {
	TimeBar::TimeBar(float maxWidth, float height, float screenCenterX, float screenHeight)
		:m_maxWidth(maxWidth)
		, m_height(height)
		, m_screenCenterX(screenCenterX)
		, m_screenHeight(screenHeight) {
		m_bar.setFillColor(sf::Color::Red);
		m_bar.setSize({ maxWidth, height });
		sf::FloatRect rect = m_bar.getLocalBounds();
		m_bar.setOrigin(rect.getCenter());
		m_bar.setPosition({ screenCenterX, screenHeight - (height + 5) });
	}

	void TimeBar::Update(float fraction) {
		float width = m_maxWidth * fraction;
		m_bar.setSize({ width, m_height });
		sf::FloatRect rect = m_bar.getLocalBounds();
		m_bar.setOrigin(rect.getCenter());
		m_bar.setPosition({ m_screenCenterX, m_screenHeight - (m_height + 5) });
	}

	void TimeBar::Draw(sf::RenderWindow& window) const {
		window.draw(m_bar);
	}
}