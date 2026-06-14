#pragma once
#include <SFML/Graphics.hpp>

namespace Timber {
	class TimeBar
	{
	public:
		TimeBar(float maxWidth, float height, float screenCenterX, float screenHeight);

		/// Update the bar width based on a fraction (0.0 to 1.0)
		void Update(float fraction);
		void Draw(sf::RenderWindow& window)const;

	private:
		sf::RectangleShape m_bar;
		float m_maxWidth;
		float m_height;
		float m_screenCenterX;
		float m_screenHeight;
	};
}