#include "Branch.hpp"
#include "Math/Random.hpp"

namespace Timber {
	Branch::Branch(const sf::Texture& texture, int id)
		:m_sprite(texture), m_side(Side::None), m_id(id) {
		sf::FloatRect rect = m_sprite.getLocalBounds();
		m_sprite.setOrigin(rect.getCenter());
		SetRandomSide();
	}

	void Branch::SetSide(Side side) {
		m_side = side;
		ApplySidePosition();
	}

	void Branch::SetRandomSide() {
		int roll = Engine::Random::IntRange(0, 4);
		float height = (BRANCH_SPACING * m_id) + BRANCH_TOP_OFFSET;
		switch (roll)
		{
		case 0:
			m_side = Side::Left;
			m_sprite.setRotation(sf::degrees(180));
			m_sprite.setPosition({ BRANCH_LEFT_X, height });
			break;
		case 1:
			m_side = Side::Right;
			m_sprite.setRotation(sf::degrees(0));
			m_sprite.setPosition({ BRANCH_RIGHT_X, height });
			break;
		default:
			m_side = Side::None;
			m_sprite.setPosition({ BRANCH_OFFSCREEN_X, height });
			break;
		}
	}

	void Branch::ResetBranch() {
		m_side = Side::None;
		float height = (BRANCH_SPACING * m_id) + BRANCH_TOP_OFFSET;
		m_sprite.setPosition({ BRANCH_OFFSCREEN_X, height });
	}

	Side Branch::GetSide() const {
		return m_side;
	}

	const sf::Sprite& Branch::GetSprite() const {
		return m_sprite;
	}

	void Branch::Draw(sf::RenderWindow& window) const {
		window.draw(m_sprite);
	}

	void Branch::ApplySidePosition() {
		float height = (BRANCH_SPACING * m_id) + BRANCH_TOP_OFFSET;
		if (m_side == Side::Left) {
			m_sprite.setPosition({ BRANCH_LEFT_X, height });
			m_sprite.setRotation(sf::degrees(180));
		}
		else if (m_side == Side::Right) {
			m_sprite.setPosition({ BRANCH_RIGHT_X, height });
			m_sprite.setRotation(sf::degrees(0));
		}
		else {
			m_sprite.setPosition({ BRANCH_OFFSCREEN_X, height });
		}
	}
}