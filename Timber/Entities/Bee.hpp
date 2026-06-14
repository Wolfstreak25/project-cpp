#pragma once

#include "Entity/MovingEntity.hpp"
namespace Timber {
	class Bee : public Engine::MovingEntity
	{
	public:
		Bee(const sf::Texture& texture);

	protected:
		void Spawn()override;
		bool IsOutOfBounds()override;
		void Move(float dt)override;
	};
}