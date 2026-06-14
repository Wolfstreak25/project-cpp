#pragma once
namespace Timber {
	class TimeSystem
	{
	public:
		TimeSystem() = default;
		void Reset(float initialTime);
		void Update(float dt);
		void AddTime(float seconds);
		float GetTimeRemaining()const;
		bool IsExpired() const;

		/// Return a 0.0 to 1.0 value representing time fraction remaining.
		float GetFraction() const;
	private:
		float m_timeRemaining = 0.0f;
		float m_initialTime = 0.0f;
	};
}