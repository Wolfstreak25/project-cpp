#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace Engine {
	class Timer
	{
	public:
		Timer();
		void Start();
		void Stop();
		void Reset();
		float GetElapsedSeconds() const;
		bool IsRunning()const;
	private:
		sf::Clock m_clock;
		float m_accumulated;
		bool m_running;
	};
}