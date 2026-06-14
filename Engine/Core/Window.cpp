#include "Window.hpp"

namespace Engine {
	Window::Window(const std::string& title, unsigned int width, unsigned int height)
		:m_window(sf::VideoMode({ width, height }), title) {
	}

	bool Window::IsOpen()const {
		return m_window.isOpen();
	}

	void Window::Close() {
		m_window.close();
	}

	void Window::Clear() {
		m_window.clear();
	}

	void Window::Display() {
		m_window.display();
	}

	sf::RenderWindow& Window::GetRaw() {
		return m_window;
	}

	sf::Vector2u Window::GetSize() const {
		return m_window.getSize();
	}
}