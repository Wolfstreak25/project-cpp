#pragma once
#include <SFML/Graphics.hpp>
namespace Engine {
	class Entity {
	public:
		virtual ~Entity() = default;
		virtual void Update(float dt) = 0;
		virtual void Draw(sf::RenderWindow& window) const = 0;
	};
}