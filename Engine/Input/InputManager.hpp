#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <map>

namespace Engine {
	/// Manages keyboard input with a callback-based binding system.
	class InputManager {
	public:
		using KeyCallback = std::function<void()>;

		InputManager() = default;

		/// Bind a callback to a key press.
		void BindKeyPressed(sf::Keyboard::Key key, KeyCallback callback);

		/// Bind a callback to a key release.
		void BindKeyReleased(sf::Keyboard::Key key, KeyCallback callback);

		/// Process on SFML event and fire any matching callbacks.
		void HandleEvent(const sf::Event& event);

		/// Check if a key is currently held down (real-time polling).
		static bool IsKeyHeld(sf::Keyboard::Key key);

		/// clear all bindings
		void ClearBindings();

	private:
		std::map<sf::Keyboard::Key, KeyCallback> m_pressBindings;
		std::map<sf::Keyboard::Key, KeyCallback> m_releaseBindings;
	};
}