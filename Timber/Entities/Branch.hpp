#pragma once
#include "Config/Constants.hpp"
#include <SFML/Graphics.hpp>

namespace Timber {
	class Branch
	{
	public:
		Branch(const sf::Texture& texture, int id);
		void SetSide(Side side);
		void SetRandomSide();
		void ResetBranch();
		Side GetSide() const;
		const sf::Sprite& GetSprite() const;
		void Draw(sf::RenderWindow& window) const;
	private:
		void ApplySidePosition();
		sf::Sprite m_sprite;
		Side m_side;
		int m_id;
	};
}