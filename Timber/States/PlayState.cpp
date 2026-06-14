#include "PlayState.hpp"
#include "Utilities/Logger.hpp"

namespace Timber
{

PlayState::PlayState(Engine::Application& app)
    : m_app(app)
    , m_subState(SubState::Paused)
    , m_acceptInput(false)
{
}

void PlayState::OnEnter()
{
    Engine::Logger::Info("PlayState: OnEnter");

    // --- Load textures ---
    auto& textures = m_app.GetTextures();
    textures.Load("assets/graphics/background.png");
    textures.Load("assets/graphics/tree.png");
    textures.Load("assets/graphics/bee.png");
    textures.Load("assets/graphics/cloud.png");
    textures.Load("assets/graphics/branch.png");
    textures.Load("assets/graphics/player.png");
    textures.Load("assets/graphics/axe.png");
    textures.Load("assets/graphics/log.png");
    textures.Load("assets/graphics/rip.png");

    // --- Load sounds ---
    auto& audio = m_app.GetAudio();
    audio.LoadSound("assets/sound/chop.wav");
    audio.LoadSound("assets/sound/death.wav");
    audio.LoadSound("assets/sound/out_of_time.wav");

    // --- Load fonts ---
    auto& fonts = m_app.GetFonts();
    fonts.Load("assets/fonts/KOMIKAP_.ttf");

    // --- Create scene sprites ---
    m_background = std::make_unique<sf::Sprite>(textures.Get("assets/graphics/background.png"));

    m_tree = std::make_unique<sf::Sprite>(textures.Get("assets/graphics/tree.png"));
    m_tree->setPosition({TREE_X, 0.0f});

    // --- Create entities ---
    // 1 bee
    m_movingEntities.push_back(std::make_unique<Bee>(textures.Get("assets/graphics/bee.png")));

    // 3 clouds
    for (int i = 0; i < 3; ++i)
    {
        m_movingEntities.push_back(std::make_unique<Cloud>(textures.Get("assets/graphics/cloud.png")));
    }

    // Player (includes axe, log, rip sprites)
    m_player = std::make_unique<Player>(
        textures.Get("assets/graphics/player.png"),
        textures.Get("assets/graphics/axe.png"),
        textures.Get("assets/graphics/log.png"),
        textures.Get("assets/graphics/rip.png"));

    // --- Initialize systems ---
    m_branchSystem.Init(textures.Get("assets/graphics/branch.png"), NUM_BRANCHES);
    m_scoreSystem.Reset();
    m_timeSystem.Reset(INITIAL_TIME);

    // --- Create UI ---
    m_hud = std::make_unique<HUD>(fonts.Get("assets/fonts/KOMIKAP_.ttf"));
    m_timeBar = std::make_unique<TimeBar>(
        TIME_BAR_WIDTH, TIME_BAR_HEIGHT,
        static_cast<float>(WINDOW_WIDTH_CENTER),
        static_cast<float>(WINDOW_HEIGHT));

    // --- Initial state ---
    m_subState = SubState::Paused;
    m_acceptInput = false;
}

void PlayState::OnExit()
{
    Engine::Logger::Info("PlayState: OnExit");

    m_movingEntities.clear();
    m_player.reset();
    m_hud.reset();
    m_timeBar.reset();
    m_background.reset();
    m_tree.reset();
}

void PlayState::HandleEvent(const sf::Event& event)
{
    if (auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        // Escape always quits
        if (keyPressed->code == sf::Keyboard::Key::Escape)
        {
            m_app.Quit();
            return;
        }

        // Enter starts/restarts the game
        if (keyPressed->code == sf::Keyboard::Key::Enter)
        {
            if (m_subState == SubState::Paused || m_subState == SubState::GameOver)
            {
                StartGame();
            }
            return;
        }

        // Chop input (only when playing and input accepted)
        if (m_subState == SubState::Playing && m_acceptInput)
        {
            if (keyPressed->code == sf::Keyboard::Key::Left)
            {
                HandleChop(Side::Left);
            }
            else if (keyPressed->code == sf::Keyboard::Key::Right)
            {
                HandleChop(Side::Right);
            }
        }
    }
    else if (event.getIf<sf::Event::KeyReleased>())
    {
        // Re-enable input after key release (prevents auto-repeat chop)
        if (m_subState == SubState::Playing)
        {
            m_acceptInput = true;
        }
    }
}

void PlayState::Update(float dt)
{
    if (m_subState == SubState::Playing)
    {
        // Update time
        m_timeSystem.Update(dt);

        if (m_timeSystem.IsExpired())
        {
            m_subState = SubState::GameOver;
            m_acceptInput = false;
            m_hud->SetMessage("Out of Time!!", sf::Color::Red);
            m_app.GetAudio().PlaySound("assets/sound/out_of_time.wav");
            return;
        }

        // Update moving entities (bee, clouds)
        for (auto& entity : m_movingEntities)
        {
            entity->Update(dt);
        }

        // Update player (log animation)
        m_player->Update(dt);

        // Update time bar
        m_timeBar->Update(m_timeSystem.GetFraction());

        // Update HUD score
        m_hud->SetScore(m_scoreSystem.GetScore());
    }

    // Update FPS display regardless of state
    m_hud->SetFPS(static_cast<float>(m_app.GetClock().GetFPS()));
}

void PlayState::Draw(sf::RenderWindow& window)
{
    // Background
    window.draw(*m_background);

    // Tree
    window.draw(*m_tree);

    // Moving entities (clouds and bee)
    for (auto& entity : m_movingEntities)
    {
        entity->Draw(window);
    }

    // Branches
    m_branchSystem.Draw(window);

    // Player (includes axe, log, rip)
    m_player->Draw(window);

    // HUD (score, fps, message)
    bool showMessage = (m_subState != SubState::Playing);
    m_hud->Draw(window, showMessage);

    // Time bar
    m_timeBar->Draw(window);
}

void PlayState::StartGame()
{
    m_subState = SubState::Playing;
    m_acceptInput = true;

    // Reset all systems
    m_scoreSystem.Reset();
    m_timeSystem.Reset(INITIAL_TIME);
    m_branchSystem.ResetAll();

    // Reset player
    m_player->Reset();

    // Reset UI
    m_hud->SetScore(0);
    m_hud->HideMessage();

    Engine::Logger::Info("PlayState: Game started");
}

void PlayState::HandleChop(Side side)
{
    // Perform the chop
    if (side == Side::Left)
    {
        m_player->ChopLeft();
    }
    else
    {
        m_player->ChopRight();
    }

    // Score and time bonus
    m_scoreSystem.AddPoint();
    m_timeSystem.AddTime(m_scoreSystem.GetTimeBonus());

    // Shift branches down
    m_branchSystem.ShiftBranches();

    // Play chop sound
    m_app.GetAudio().PlaySound("assets/sound/chop.wav");

    // Update HUD
    m_hud->SetScore(m_scoreSystem.GetScore());

    // Disable input until key is released
    m_acceptInput = false;

    // Check if player was squished by the new bottom branch
    CheckCollision();
}

void PlayState::CheckCollision()
{
    Side bottomBranch = m_branchSystem.GetBottomBranchSide();
    if (bottomBranch == m_player->GetSide())
    {
        // Player is squished!
        m_player->Kill();
        m_subState = SubState::GameOver;
        m_acceptInput = false;

        m_app.GetAudio().PlaySound("assets/sound/death.wav");
        m_hud->SetMessage("SQUISHED!!", sf::Color::Red);

        Engine::Logger::Info("PlayState: Player squished!");
    }
}

} // namespace Timber
