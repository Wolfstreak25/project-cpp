#pragma once
#include <SFML/Graphics//RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <optional>
#include <string>

namespace Engine {
	class Window
	{
	public:
		Window(const std::string& title, unsigned int width, unsigned int height);
		~Window() = default;

		bool IsOpen() const;
		void Close();
		void Clear();
		void Display();

		/// Poll the next event. Returns std::nullopt if no events remain.
		std::optional<sf::Event>PollEvent();
		sf::RenderWindow& GetRaw();
		sf::Vector2u GetSize() const;

	private:
		sf::RenderWindow m_window;
	};
}