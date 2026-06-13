#include "Logger.hpp"
namespace Engine {
	constexpr const char* RESET = "\033[0m";
	void Logger::Log(Level level, const std::string& message) {
		std::cout << GetColor(level) << LevelToString(level) << message << RESET << std::endl;
	}

	std::string Logger::LevelToString(Level level) {
		switch (level)
		{
		case Level::Info:
			return "[INFO] : ";
		case Level::Warning:
			return "[WARNING] : ";
		case Level::Error:
			return "[ERROR] : ";
		default:
			break;
		}
		return "[UNKNOWN] : ";
	}
	const char* Logger::GetColor(Level level)
	{
		switch (level)
		{
		case Level::Info:
			return "\033[37m"; // White
		case Level::Warning:
			return "\033[33m"; // Yellow
		case Level::Error:
			return "\033[31m"; // Red
		default:
			return "\033[0m";
		}
	}
}
