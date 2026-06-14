#include "GameClock.hpp"

namespace Engine {
	GameClock::GameClock() :m_fps(0.0f), m_timeAccumulator(0.0f), m_frameCount(0) {
	}

	float GameClock::Restart() {
		float dt = m_clock.restart().asSeconds();

		m_timeAccumulator += dt;
		m_frameCount++;
		if (m_timeAccumulator >= 1.0f) {
			m_fps = static_cast<float>(m_frameCount) / m_timeAccumulator;
			m_timeAccumulator -= 1.0f;
			m_frameCount = 0;
		}
		return dt;
	}

	int GameClock::GetFPS() const {
		return static_cast<int>(m_fps);
	}
}