
#include "nostrautils\dat_alg\Random.hpp"

namespace NOU::NOU_DAT_ALG
{
	Random::Random(Seed seed)
	{
		if (seed == USE_TIME_AS_SEED)
		{
			std::time_t currentTime = std::time(nullptr); //current system time
			m_seed = currentTime;
		}
		else
		{
			m_seed = seed;
		}
	}

	void Random::setSeed(Seed seed)
	{
		m_seed = seed;
	}

	uint64 Random::rand()
	{
		const Value A = 6364136223846793005L;
		const Value b = 1442695040888963407L;
		const Value m = -1; //maximum value of uint64
		m_seed = (A* m_seed + b) % m;
		return m_seed;
	}

	typename Random::Value Random::rand(Value a, Value b)
	{
		Value r = rand();

		r %= (b + 1) - a;
		r += a;
		
		return r;
	}
}