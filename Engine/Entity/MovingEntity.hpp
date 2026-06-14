#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

namespace Engine {
	/// A MovingEntity automatically spawns itself when inactive,
	/// moves each frame, and deactivates when out of bounds.
	class MovingEntity : public Entity {
	public:
		MovingEntity(const sf::Texture& texture);
		virtual ~MovingEntity() = default;

		void Update(float dt) override;
		void Draw(sf::RenderWindow& window) const override;

		const sf::Sprite& GetSprite() const;
		bool IsActive() const;
	protected:
		virtual void Spawn() = 0;
		virtual bool IsOutOfBounds() = 0;
		virtual void Move(float dt) = 0;

		sf::Sprite m_sprite;
		float m_speed = 0.0f;
		bool m_active = false;
	};
}