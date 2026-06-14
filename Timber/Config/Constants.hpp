#pragma once

#include <SFML/System/Vector2.hpp>

namespace Timber
{
	// --- Window ---
	inline constexpr unsigned int WINDOW_WIDTH = 1920;
	inline constexpr unsigned int WINDOW_HEIGHT = 1080;
	inline constexpr unsigned int WINDOW_WIDTH_CENTER = 960;
	inline constexpr unsigned int WINDOW_HEIGHT_CENTER = 540;
	inline constexpr float OFFSCREEN_LEFT = -300.f;
	inline constexpr float OFFSCREEN_RIGHT = WINDOW_WIDTH + 200.f;

	// These must be const (not constexpr) because sf::Vector2f constructor is not constexpr in SFML 3
	inline const sf::Vector2f WINDOW_CENTER = { WINDOW_WIDTH_CENTER, WINDOW_HEIGHT_CENTER };
	inline const sf::Vector2f WINDOW_CENTER_BOTTOM = { WINDOW_WIDTH_CENTER, WINDOW_HEIGHT };

	// --- Gameplay ---
	inline constexpr int NUM_BRANCHES = 6;
	inline constexpr float INITIAL_TIME = 6.0f;
	inline constexpr float TIME_BAR_WIDTH = 400.0f;
	inline constexpr float TIME_BAR_HEIGHT = 80.0f;

	// --- Player positions ---
	inline constexpr float PLAYER_LEFT_X = 580.0f;
	inline constexpr float PLAYER_RIGHT_X = 1200.0f;
	inline constexpr float PLAYER_Y = 720.0f;
	inline constexpr float AXE_POS_LEFT = 700.0f;
	inline constexpr float AXE_POS_RIGHT = 1075.0f;
	inline constexpr sf::Vector2f PLAYER_POS_LEFT(PLAYER_LEFT_X, PLAYER_Y);
	inline constexpr sf::Vector2f PLAYER_POS_RIGHT(PLAYER_RIGHT_X, PLAYER_Y);

	// --- Branch positions ---
	inline constexpr float BRANCH_LEFT_X = 660.0f;
	inline constexpr float BRANCH_RIGHT_X = 1330.0f;
	inline constexpr float BRANCH_OFFSCREEN_X = 3000.0f;
	inline constexpr float BRANCH_SPACING = 150.0f;
	inline constexpr float BRANCH_TOP_OFFSET = 50.0f;

	// --- Tree ---
	inline constexpr float TREE_X = 810.0f;

	// --- Log ---
	inline constexpr float LOG_SPEED_X = 5000.0f;
	inline constexpr float LOG_SPEED_Y = -1500.0f;

	// --- Enums ---
	enum class Side
	{
		None,
		Left,
		Right
	};
}