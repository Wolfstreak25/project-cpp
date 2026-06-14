#include "EventBus.hpp"

namespace Engine {
	void EventBus::Subscribe(const std::string& eventName, Callback callback) {
		m_listeners[eventName].push_back(std::move(callback));
	}

	void EventBus::Publish(const std::string& eventName) {
		auto it = m_listeners.find(eventName);
		if (it != m_listeners.end()) {
			for (auto& _callback : it->second) {
				_callback();
			}
		}
	}

	void EventBus::Clear(const std::string& eventName) {
		m_listeners.erase(eventName);
	}

	void EventBus::ClearAll() {
	}
}