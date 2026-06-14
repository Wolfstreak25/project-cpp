#pragma once
#include <string>
namespace Engine {
	/// Predefined event name constants to avoid typos
	/// Game-specific events should be defined in the game project.
	namespace Events {
		inline constexpr const char* APP_QUIT = "app:quit";
		inline constexpr const char* STATE_PUSH = "state:push";
		inline constexpr const char* STATE_POP = "state:pop";
	}
}