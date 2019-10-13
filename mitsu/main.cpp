#include <iostream>
#include <random>
#include <string>
#include <limits>

class XorOshiro128p {
private:
	uint_fast64_t seed[2];

	inline uint_fast64_t splitmix64(uint_fast64_t z) {
		z += 0x9e3779b97f4a7c15;
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
		return z ^ (z >> 31);
	}

public:
	using result_type = uint_fast64_t;

	XorOshiro128p() {
		std::random_device seeder;
		uint_fast64_t seed = seeder();
		
		this->seed[0] = splitmix64(seed);
		this->seed[1] = splitmix64(this->seed[0]);
	}
	XorOshiro128p(uint_fast64_t seed) {
		if(seed == 0) {
			std::random_device seeder;
			seed = seeder();
		}

		this->seed[0] = splitmix64(seed);
		this->seed[1] = splitmix64(this->seed[0]);
	}

	static constexpr result_type min() {
		return std::numeric_limits<uint_fast64_t>::min();
	}

	static constexpr result_type max() {
		return std::numeric_limits<uint_fast64_t>::max();
	}

	result_type operator()() {
		uint_fast64_t s0 = this->seed[0], s1 = this->seed[1], result = s0 + s1;
		s1 ^= s0;
		this->seed[0] = ((s0 << 55) | (s0 >> (64 - 55))) ^ s1 ^ (s1 << 14);
		this->seed[1] = ((s1 << 36) | (s1 >> (64 - 36)));
		return result;
	}
};

int main() {
	int rangeMin = 0, rangeMax = 9999;

	std::random_device seed;
	XorOshiro128p engine(seed());
	std::uniform_int_distribution<int> dist(rangeMin, rangeMax);

	/**  The sloppy codes below are displaying histogram.
			It is not directly related to PRNG.						***/

	int division = 30;
	double scale = 0.2;
	int classWidth = (rangeMax - rangeMin + 1) / division;
	std::vector<int> hist(division + 1, 0);							// "+1" is not divisible5 datas. Not helpful.
	
	int rnd;
	for(size_t i = 0; i < 10000; i++) {
		rnd = dist(engine);
		hist[rnd / classWidth]++;
	}

	for(auto i: hist) std::cout << std::string((int)(i * scale), '*') << std::endl;

	return 0;
}