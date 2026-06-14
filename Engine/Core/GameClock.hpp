#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace Engine {
	class GameClock
	{
	public:
		GameClock();

		/// call once per frame. Returns delta time in seconds.
		float Restart();

		/// Get the smoothed FPS value (updated once per second).
		int GetFPS()const;

	private:
		sf::Clock m_clock;
		float m_fps;
		float m_timeAccumulator;
		int m_frameCount;
	};
}