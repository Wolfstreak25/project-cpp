#include "Core/Application.hpp"
#include "Math/Random.hpp"
#include "Utilities/Logger.hpp"

int main() {
	Engine::Random::Seed();
	Engine::Application app("Timber!!!", 1920, 1080);
	app.Run();
	return 0;
}