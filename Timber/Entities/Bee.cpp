#include "Bee.hpp"
#include "Config/Constants.hpp"
#include "Math/Random.hpp"

namespace Timber {
	Bee::Bee(const sf::Texture& texture) :MovingEntity(texture) {
		m_sprite.setPosition({ OFFSCREEN_RIGHT,m_sprite.getPosition().y });
	}

	void Bee::Spawn() {
		float height = static_cast<float>(Engine::Random::IntRange(500, 999));
		m_sprite.setPosition({ OFFSCREEN_RIGHT, height });
		m_speed = static_cast<float>(Engine::Random::IntRange(200, 399));
		m_active = true;
	}

	bool Bee::IsOutOfBounds() {
		return (m_sprite.getPosition().x < -100);
	}

	void Bee::Move(float dt) {
		m_sprite.move({ -m_speed * dt, 0.0f });
	}
}