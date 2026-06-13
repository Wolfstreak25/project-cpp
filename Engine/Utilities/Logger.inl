namespace Engine {
	template<typename T>
	void AppendToStream(std::ostringstream& oss, T&& value)
	{
		oss << std::forward<T>(value);
	}

	template<typename T, typename... Rest>
	void AppendToStream(std::ostringstream& oss,
		T&& value,
		Rest&&... rest)
	{
		oss << std::forward<T>(value) << ' ';
		AppendToStream(oss,
			std::forward<Rest>(rest)...);
	}

	template<typename... Args>
	void Logger::Info(Args&&... args)
	{
		std::ostringstream oss;
		(oss << ... << args);
		Logger::Log(Level::Info, oss.str());
	}

	template<typename... Args>
	void Logger::Warning(Args&&... args)
	{
		std::ostringstream oss;
		(oss << ... << args);
		Logger::Log(Level::Warning, oss.str());
	}

	template<typename... Args>
	void Logger::Error(Args&&... args)
	{
		std::ostringstream oss;
		(oss << ... << args);
		Logger::Log(Level::Error, oss.str());
	}
}