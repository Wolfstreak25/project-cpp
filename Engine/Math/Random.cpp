#include "Math/Random.hpp"
namespace Engine {
	std::mt19937& Random::GetEngine() {
		static std::mt19937 engine;
		return engine;
	}
	void Random::Seed() {
		std::random_device rd;
		GetEngine().seed(rd());
	}

	void Random::Seed(unsigned int seed) {
		GetEngine().seed(seed);
	}

	int Random::IntRange(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(GetEngine());
	}

	float Random::FloatRange(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(GetEngine());
	}
}