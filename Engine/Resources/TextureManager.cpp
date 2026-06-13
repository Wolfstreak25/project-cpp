#include "TextureManager.hpp"
#include "Utilities/Logger.hpp"
#include <stdexcept>

namespace Engine {
	bool TextureManager::Load(const std::string& filePath) {
		sf::Texture texture;
		if (!texture.loadFromFile(filePath)) {
			Logger::Error("TextureManager : Failed to load texture :", filePath);
			return false;
		}
		m_textures[filePath] = std::move(texture);
		Logger::Info("TextureManager : Loaded from :", filePath);
		return true;
	}

	sf::Texture& TextureManager::Get(const std::string& filePath) {
		auto it = m_textures.find(filePath);
		if (it == m_textures.end()) {
			throw std::runtime_error("TextureManager : Texture not found :" + filePath);
		}
		return it->second;
	}

	bool TextureManager::Has(const std::string& filePath) const {
		return m_textures.find(filePath) != m_textures.end();
	}

}