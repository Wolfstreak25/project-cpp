#include "Core/Application.hpp"
#include "Math/Random.hpp"
#include "Utilities/Logger.hpp"
#include "States/PlayState.hpp"
#include <memory>

int main()
{
    Engine::Random::Seed();

    Engine::Application app("Timber!!!", 1920, 1080);

    app.GetStateMachine().PushState(std::make_unique<Timber::PlayState>(app));

    app.Run();

    return 0;
}
