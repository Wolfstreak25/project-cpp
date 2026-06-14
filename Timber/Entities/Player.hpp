#pragma once
#include "Config/Constants.hpp"
#include <SFML/Graphics.hpp>

namespace Timber {
	class Player
	{
	public:
		Player(const sf::Texture& playerTex, const sf::Texture& axeTex, const sf::Texture& logTex, const sf::Texture& ripTex);
		void ChopLeft();
		void ChopRight();
		void Kill();
		void Reset();
		void Update(float dt);
		void Draw(sf::RenderWindow& window) const;
		Side GetSide() const;
		bool IsLogActive() const;

	private:
		sf::Sprite m_sprite;
		sf::Sprite m_axeSprite;
		sf::Sprite m_logSprite;
		sf::Sprite m_ripSprite;

		Side m_side;
		bool m_alive;

		bool m_logActive;
		float m_logSpeedX;
		float m_logSpeedY;
	};
}