#include "Cloud.hpp"
#include "Config/Constants.hpp"
#include "Math/Random.hpp"

namespace Timber {
	Cloud::Cloud(const sf::Texture& texture) :MovingEntity(texture) {
		m_sprite.setPosition({ OFFSCREEN_LEFT, m_sprite.getPosition().y });
	}
	void Cloud::Spawn() {
		float height = static_cast<float>(Engine::Random::IntRange(0, 449));
		m_sprite.setPosition({ OFFSCREEN_LEFT, height });
		m_speed = static_cast<float>(Engine::Random::IntRange(50, 199));
		m_active = true;
	}

	bool Cloud::IsOutOfBounds() {
		return (m_sprite.getPosition().x > WINDOW_WIDTH);
	}

	void Cloud::Move(float dt) {
		m_sprite.move({ m_speed * dt, 0.0f });
	}
}