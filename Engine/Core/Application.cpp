#include "Application.hpp"
#include "Utilities/Logger.hpp"

namespace Engine {
	Application::Application(const std::string& title,
		unsigned int width, unsigned int height)\
		: m_window(title, width, height), m_running(true) {
		Logger::Info("Application Started");
	}

	void Application::Run() {
		while (m_running && m_window.IsOpen()) {
			float dt = m_clock.Restart();

			// 1. Poll events
			while (auto event = m_window.PollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					Quit();
					return;
				}

				// Forward to input manager
				m_input.HandleEvent(*event);

				// Forward to current State
				m_stateMachine.HandleEvent(*event);
			}

			// 2. Update current state
			m_stateMachine.Update(dt);

			// 3. Render
			m_window.Clear();
			m_stateMachine.Draw(m_window.GetRaw());
			m_window.Display();

			// 4. If state stack is empty, quit
			if (m_stateMachine.IsEmpty()) {
				Quit();
			}
		}
		Logger::Info("Application exiting");
	}

	void Application::Quit() {
		m_running = false;
		m_window.Close();
	}

	Window& Application::GetWindow() {
		return m_window;
	}

	StateMachine& Application::GetStateMachine() {
		return m_stateMachine;
	}

	TextureManager& Application::GetTextures() {
		return m_textures;
	}

	AudioManager& Application::GetAudio() {
		return m_audio;
	}

	FontManager& Application::GetFonts() {
		return m_fonts;
	}

	InputManager& Application::GetInput() {
		return m_input;
	}

	EventBus& Application::GetEventBus() {
		return m_eventBus;
	}

	GameClock& Application::GetClock() {
		return m_clock;
	}
}