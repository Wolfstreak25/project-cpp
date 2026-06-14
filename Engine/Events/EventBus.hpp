#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace Engine {
	/// simple string-based publish/subscribe event bus.
	class EventBus {
	public:
		using Callback = std::function<void()>;
		EventBus() = default;

		/// subscribe a callback to fire when eventName is published.
		void Subscribe(const std::string& eventName, Callback callback);

		/// Publish an event - invokes all subscriber in order.
		void Publish(const std::string& eventName);

		/// Remove all subscriber for given events.
		void Clear(const std::string& eventName);

		/// Remove all subscriber for all events.
		void ClearAll();
	private:
		std::map<std::string, std::vector<Callback>> m_listeners;
	};
}