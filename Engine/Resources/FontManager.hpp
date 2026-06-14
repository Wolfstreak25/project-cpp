#pragma once
#include <SFML/Graphics/Font.hpp>
#include <map>
#include <string>

namespace Engine {
	class FontManager {
	public:
		FontManager() = default;

		/// Load a font from file and store it under given id.
		bool Load(const std::string& filePath);

		/// Retrieve a previously loaded font;
		sf::Font& Get(const std::string& filePath);

		/// check if a font is loaded
		bool Has(const std::string& filePath) const;

	private:
		std::map<std::string, sf::Font> m_fonts;
	};
}