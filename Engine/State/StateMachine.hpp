#pragma once
#include "State.hpp"
#include <memory>
#include <vector>

namespace Engine {
	/// Stack-based state machine. The topmost state receives events/update/draws.
	class StateMachine
	{
	public:
		StateMachine() = default;

		/// Push a new state onto the stack. Calls OnEnter().
		void PushState(std::unique_ptr<State> state);

		/// Pop the top state. Call OnExit().
		void PopState();

		/// Replace the top state (pop + push)
		void ChangeState(std::unique_ptr<State> state);

		/// Get the currently active (top) state. Returns nullptr if empty.
		State* CurrentState() const;

		/// Check if the stack is empty.
		bool IsEmpty() const;

		/// Forward calls to the current state.
		void HandleEvent(const sf::Event& event);
		void Update(float dt);
		void Draw(sf::RenderWindow& window);


	private:
		std::vector<std::unique_ptr<State>> m_states;
	};
}