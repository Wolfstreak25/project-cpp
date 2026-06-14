#pragma once
#include "GameClock.hpp"
#include "Window.hpp"
#include "Events/EventBus.hpp"
#include "Input/InputManager.hpp"
#include "Resources/AudioManager.hpp"
#include "Resources/FontManager.hpp"
#include "Resources/TextureManager.hpp"
#include "State/StateMachine.hpp"
#include <string>

namespace Engine {
	class Application
	{
	public:
		Application(const std::string& title, unsigned int width, unsigned int height);
		~Application() = default;

		/// Run the main game loop. Blocks until the window is closed.
		void Run();

		/// Signal the application to quit.
		void Quit();

		Window& GetWindow();
		StateMachine& GetStateMachine();
		TextureManager& GetTextures();
		AudioManager& GetAudio();
		FontManager& GetFonts();
		InputManager& GetInput();
		EventBus& GetEventBus();
		GameClock& GetClock();
	private:
		Window m_window;
		GameClock m_clock;
		StateMachine m_stateMachine;
		TextureManager m_textures;
		AudioManager m_audio;
		FontManager m_fonts;
		InputManager m_input;
		EventBus m_eventBus;
		bool m_running;
	};
}
