#pragma once

#include "Config/Constants.hpp"
#include "Core/Application.hpp"
#include "Entities/Bee.hpp"
#include "Entities/Cloud.hpp"
#include "Entities/Player.hpp"
#include "State/State.hpp"
#include "Systems/BranchSystem.hpp"
#include "Systems/ScoreSystem.hpp"
#include "Systems/TimeSystem.hpp"
#include "UI/HUD.hpp"
#include "UI/TimeBar.hpp"
#include <memory>
#include <vector>

namespace Timber
{

class PlayState : public Engine::State
{
public:
    PlayState(Engine::Application& app);

    void OnEnter() override;
    void OnExit() override;
    void HandleEvent(const sf::Event& event) override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

private:
    void HandleChop(Side side);
    void StartGame();
    void CheckCollision();

    Engine::Application& m_app;

    // Sub-state within PlayState
    enum class SubState
    {
        Paused,
        Playing,
        GameOver
    };
    SubState m_subState;
    bool m_acceptInput;

    // Scene (unique_ptr because SFML 3 Sprite requires texture at construction)
    std::unique_ptr<sf::Sprite> m_background;
    std::unique_ptr<sf::Sprite> m_tree;

    // Entities
    std::vector<std::unique_ptr<Engine::MovingEntity>> m_movingEntities;
    std::unique_ptr<Player> m_player;

    // Systems
    BranchSystem m_branchSystem;
    ScoreSystem m_scoreSystem;
    TimeSystem m_timeSystem;

    // UI
    std::unique_ptr<HUD> m_hud;
    std::unique_ptr<TimeBar> m_timeBar;
};

} // namespace Timber
