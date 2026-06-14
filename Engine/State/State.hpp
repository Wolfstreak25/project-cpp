#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window//Event.hpp>

namespace Engine {
	class Application;

	/// Abstract base class for all game states.
	class State {
	public:
		virtual ~State() = default;
		/// Called once when the state is pushed onto the stack.
		virtual void OnEnter() {}

		/// Called once when the state is popped off the stack.
		virtual void OnExit() {}

		/// handle a SFML event (keyboard, window close, etc.)
		virtual void handleEvent(const sf::Event& event) = 0;

		/// Update game logic for this state.
		virtual void Update(float dt) = 0;

		/// Draw this state's content to the window.
		virtual void Draw(sf::RenderWindow& window) = 0;

		/// If true, states below this one on the stack are also drawn;
		virtual bool IsTransparent() const { return false; }
	};
}