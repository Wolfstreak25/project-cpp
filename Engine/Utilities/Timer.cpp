#include "Timer.hpp"
namespace Engine {
	Timer::Timer() :m_accumulated(0.0f), m_running(false) {
	}

	void Timer::Start() {
		if (!m_running) {
			m_clock.restart();
			m_running = true;
		}
	}

	void Timer::Stop() {
		if (m_running) {
			m_accumulated += m_clock.restart().asSeconds();
			m_running = false;
		}
	}

	void Timer::Reset() {
		m_accumulated = 0.0f;
		m_clock.restart();
	}

	float Timer::GetElapsedSeconds() const {
		if (m_running) {
			return m_accumulated + m_clock.getElapsedTime().asSeconds();
		}
		return m_accumulated;
	}

	bool Timer::IsRunning() const {
		return m_running;
	}
}