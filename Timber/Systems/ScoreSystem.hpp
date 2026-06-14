#pragma once
namespace Timber {
	class ScoreSystem
	{
	public:
		ScoreSystem() = default;
		void Reset();
		void AddPoint();
		int GetScore() const;

		/// calculate the time bonus for the current score.
		/// Returns the seconds to add to the timer.
		float GetTimeBonus()const;
	private:
		int m_score = 0;
	};
}