#include <SFML/Audio.hpp>
#include <map>
#include <string>

namespace Engine {
	class AudioManager {
	public:
		AudioManager() = default;
		/// Load a sound effect from a .wav file.
		bool LoadSound(const std::string& filePath);

		/// Play a previously loaded sound effect.
		void PlaySound(const std::string& filePath);

		/// Stop a specific sound.
		void StopSound(const std::string& filePath);

		/// Load and play background music (streams from file)
		bool PlayMusic(const std::string& filePath, bool loop = true);

		/// Stop the currently playing music.
		void StopMusic();

	private:
		std::map<std::string, sf::SoundBuffer> m_buffers;
		std::map<std::string, sf::Sound> m_sounds;
		sf::Music m_music;
	};
}