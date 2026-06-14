#include "ScoreSystem.hpp"
namespace Timber {
	void ScoreSystem::Reset() {
		m_score = 0;
	}

	void ScoreSystem::AddPoint() {
		m_score++;
	}

	int ScoreSystem::GetScore() const {
		return m_score;
	}

	float ScoreSystem::GetTimeBonus()const {
		if (m_score == 0) {
			return 0.0f;
		}
		return(2.0f / m_score) + 0.15f;
	}
}