#pragma once
#include <random>
namespace Engine {
	class Random {
	public:
		static void Seed();
		static void Seed(unsigned int seed);

		/// Returns a random int in [min, max] (inclusive)
		static int IntRange(int min, int max);
		/// Returns a random float in [min, max]
		static float FloatRange(float min, float max);

	private:
		static std::mt19937& GetEngine();
	};
}