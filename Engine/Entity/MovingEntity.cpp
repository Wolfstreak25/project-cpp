#include "MovingEntity.hpp"

namespace Engine {
	MovingEntity::MovingEntity(const sf::Texture& texture) : m_sprite(texture) {
	}

	void MovingEntity::Update(float dt) {
		if (!m_active) {
			Spawn();
		}
		else {
			Move(dt);
			if (IsOutOfBounds()) {
				m_active = false;
			}
		}
	}

	void MovingEntity::Draw(sf::RenderWindow& window)const {
		if (m_active) {
			window.draw(m_sprite);
		}
	}

	bool MovingEntity::IsActive()const {
		return m_active;
	}

	const sf::Sprite& MovingEntity::GetSprite()const {
		return m_sprite;
	}
}