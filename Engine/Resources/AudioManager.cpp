#include "AudioManager.hpp"
#include "Utilities/Logger.hpp"
namespace Engine {
	bool AudioManager::LoadSound(const std::string& filePath) {
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(filePath)) {
			Logger::Error("AudioManager : failed to load sound : ", filePath);
			return false;
		}
		m_buffers[filePath] = std::move(buffer);
		// TODO -  update this as it may not be safe
		m_sounds.try_emplace(
			filePath,
			m_buffers[filePath]
		);
		Logger::Info("AudioManager : Loaded : ", filePath);
		return true;
	}

	void AudioManager::PlaySound(const std::string& filePath) {
		auto it = m_sounds.find(filePath);
		if (it != m_sounds.end()) {
			it->second.play();
		}
		else {
			Logger::Warning("AudioManager: Sound ", filePath, " not found");
		}
	}

	void AudioManager::StopSound(const std::string& filePath) {
		auto it = m_sounds.find(filePath);
		if (it != m_sounds.end()) {
			it->second.stop();
		}
	}

	bool AudioManager::PlayMusic(const std::string& filePath, bool loop) {
		if (!m_music.openFromFile(filePath)) {
			Logger::Error("AudioManager : Failed to load music : ", filePath);
			return false;
		}
		m_music.setLooping(loop);
		m_music.play();
		return true;
	}

	void AudioManager::StopMusic() {
		m_music.stop();
	}
}