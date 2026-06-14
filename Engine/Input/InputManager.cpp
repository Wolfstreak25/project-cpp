#include "InputManager.hpp"

namespace Engine {
	void  InputManager::BindKeyPressed(sf::Keyboard::Key key, KeyCallback callback) {
		m_pressBindings[key] = std::move(callback);
	}

	void  InputManager::BindKeyReleased(sf::Keyboard::Key key, KeyCallback callback) {
		m_releaseBindings[key] = std::move(callback);
	}

	void InputManager::HandleEvent(const sf::Event& event) {
		if (auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
			auto it = m_pressBindings.find(keyPressed->code);
			if (it != m_pressBindings.end()) {
				it->second();
			}
		}
		else if (auto* keyReleased = event.getIf<sf::Event::KeyReleased>()) {
			auto it = m_releaseBindings.find(keyReleased->code);
			if (it != m_releaseBindings.end()) {
				it->second();
			}
		}
	}

	bool InputManager::IsKeyHeld(sf::Keyboard::Key key) {
		return sf::Keyboard::isKeyPressed(key);
	}

	void InputManager::ClearBindings() {
		m_releaseBindings.clear();
		m_pressBindings.clear();
	}
}