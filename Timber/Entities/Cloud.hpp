#pragma once
#include "Entity/MovingEntity.hpp"

namespace Timber {
	class Cloud : public Engine::MovingEntity
	{
	public:
		Cloud(const sf::Texture& texture);

	protected:
		void Spawn() override;
		bool IsOutOfBounds() override;
		void Move(float dt) override;
	};
}