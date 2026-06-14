#include "Entities/Player.hpp"

namespace Timber {
	Player::Player(const sf::Texture& playerTex,
		const sf::Texture& axeTex,
		const sf::Texture& logTex, const sf::Texture& ripTex)
		: m_sprite(playerTex), m_axeSprite(axeTex),
		m_logSprite(logTex), m_ripSprite(ripTex), m_side(Side::Left), m_alive(true),
		m_logActive(false), m_logSpeedX(0.0f), m_logSpeedY(LOG_SPEED_Y) {
		m_sprite.setPosition(PLAYER_POS_LEFT);
		m_ripSprite.setPosition(m_sprite.getPosition());
	}

	void Player::ChopLeft() {
		m_side = Side::Left;
		m_sprite.setPosition(PLAYER_POS_LEFT);
		m_axeSprite.setPosition({ AXE_POS_LEFT, m_axeSprite.getPosition().y });
		m_logSprite.setPosition({ TREE_X, PLAYER_Y });
		m_logSpeedX = LOG_SPEED_X;
		m_logActive = true;
	}

	void Player::ChopRight() {
		m_side = Side::Right;
		m_sprite.setPosition(PLAYER_POS_RIGHT);
		m_axeSprite.setPosition({ AXE_POS_RIGHT, m_axeSprite.getPosition().y });
		m_logSprite.setPosition({ TREE_X, PLAYER_Y });
		m_logSpeedX = -LOG_SPEED_X;
		m_logActive = true;
	}

	void Player::Kill() {
		m_alive = false;
		m_ripSprite.setPosition(m_sprite.getPosition());
		m_sprite.setPosition({ 2000.0f, PLAYER_Y - 60.0f });
	}

	void Player::Reset() {
		m_alive = true;
		m_side = Side::Left;
		m_sprite.setPosition(PLAYER_POS_LEFT);
		m_axeSprite.setPosition({ AXE_POS_LEFT, 830.0f });
		m_ripSprite.setPosition({ m_ripSprite.getPosition().x, 2000.0f });
		m_logActive = false;
	}

	void Player::Update(float dt) {
		if (m_logActive) {
			m_logSprite.move({ m_logSpeedX * dt, m_logSpeedY * dt });
			if (m_logSprite.getPosition().x < -100 || m_logSprite.getPosition().x > 2000) {
				m_logActive = false;
				m_logSprite.setPosition({ TREE_X, PLAYER_Y });
			}
		}
	}

	void Player::Draw(sf::RenderWindow& window) const {
		window.draw(m_sprite);
		window.draw(m_axeSprite);
		if (m_logActive) {
			window.draw(m_logSprite);
		}
		if (!m_alive) {
			window.draw(m_ripSprite);
		}
	}

	Side Player::GetSide() const {
		return m_side;
	}

	bool Player::IsLogActive() const {
		return m_logActive;
	}
}