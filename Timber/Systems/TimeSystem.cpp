#include "TimeSystem.hpp"
#include <algorithm>
namespace Timber {
	void TimeSystem::Reset(float initialTime) {
		m_initialTime = initialTime;
		m_timeRemaining = initialTime;
	}

	void TimeSystem::Update(float dt) {
		m_timeRemaining -= dt;
		if (m_timeRemaining < 0.0f) {
			m_timeRemaining = 0.0f;
		}
	}

	void TimeSystem::AddTime(float seconds) {
		m_timeRemaining += seconds;
	}

	float TimeSystem::GetTimeRemaining()const {
		return m_timeRemaining;
	}
	bool TimeSystem::IsExpired()const {
		return m_timeRemaining <= 0.0f;
	}

	float TimeSystem::GetFraction() const {
		if (m_initialTime <= 0.0f) {
			return 0.0f;
		}
		return std::clamp(m_timeRemaining / m_initialTime, 0.0f, 1.0f);
	}
}