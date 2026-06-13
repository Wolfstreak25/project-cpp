#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace Engine
{
	class Logger {
	public:
		enum class Level {
			Info,
			Warning,
			Error
		};
		static void Log(Level level, const std::string& message);

		template<typename... Args>
		static void Info(Args&&... args);

		template<typename... Args>
		static void Warning(Args&&... args);

		template<typename... Args>
		static void Error(Args&&... args);


	private:
		static std::string LevelToString(Level level);
		static const char* GetColor(Level level);
	};
}
#include "Logger.inl"