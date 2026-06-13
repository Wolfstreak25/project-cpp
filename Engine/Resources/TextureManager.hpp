#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
namespace Engine {
	class TextureManager {
	public:
		TextureManager() = default;

		/// Load a texture from file and cache it under the given id.
		/// returns true on success
		bool Load(const std::string& filePath);

		/// retrives a previously loaded texture by id
		/// Throws std::runtime_error if not found
		sf::Texture& Get(const std::string& filePath);

		/// check if a texture is already loaded
		bool Has(const std::string& filePath) const;

	private:
		std::map<std::string, sf::Texture> m_textures;
	};
}