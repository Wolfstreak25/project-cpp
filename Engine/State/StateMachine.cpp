#include "StateMachine.hpp"

namespace Engine {
	void StateMachine::PushState(std::unique_ptr<State> state) {
		state->OnEnter();
		m_states.push_back(std::move(state));
	}

	void StateMachine::PopState() {
		if (!m_states.empty()) {
			m_states.back()->OnExit();
			m_states.pop_back();
		}
	}

	void StateMachine::ChangeState(std::unique_ptr<State> state) {
		PopState();
		PushState(std::move(state));
	}

	State* StateMachine::CurrentState() const {
		if (m_states.empty()) {
			return nullptr;
		}
		return m_states.back().get();
	}

	bool StateMachine::IsEmpty() const {
		return m_states.empty();
	}

	void StateMachine::HandleEvent(const sf::Event& event) {
		if (auto* state = CurrentState()) {
			state->HandleEvent(event);
		}
	}

	void StateMachine::Update(float dt) {
		if (auto* state = CurrentState()) {
			state->Update(dt);
		}
	}

	void StateMachine::Draw(sf::RenderWindow& window) {
		for (size_t i = 0; i < m_states.size(); ++i) {
			if (i == m_states.size() - 1 || m_states[i + 1]->IsTransparent()) {
				m_states[i]->Draw(window);
			}
		}
	}
}