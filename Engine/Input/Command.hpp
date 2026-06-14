#pragma once
namespace Engine {
	/// Abstract command pattern for input actions.
	/// Subclass this to create game-specific commands.
	class Command {
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};
}