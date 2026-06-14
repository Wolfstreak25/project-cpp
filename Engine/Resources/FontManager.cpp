#include "FontManager.hpp"
#include "Utilities/Logger.hpp"
#include <stdexcept>
namespace Engine {
	bool FontManager::Load(const std::string& filePath) {
		sf::Font font;
		if (!font.openFromFile(filePath)) {
			Logger::Error("FontManager : Failed to load font", filePath);
			return false;
		}
		m_fonts[filePath] = std::move(font);
		Logger::Info("FontManager : Loaded", filePath);
		return true;
	}

	sf::Font& FontManager::Get(const std::string& filePath) {
		auto it = m_fonts.find(filePath);
		if (it == m_fonts.end()) {
			throw std::runtime_error("FontManager : Font not found : " + filePath);
		}
		return it->second;
	}

	bool FontManager::Has(const std::string& filePath)const {
		return m_fonts.find(filePath) != m_fonts.end();
	}
}