#include "nostrautils\dat_alg\Hashing.hpp"

namespace NOU::NOU_DAT_ALG
{
	NOU::sizeType hashValue(NOU::sizeType value, NOU::sizeType max) 
	{
		const NOU::int16 PRIME = 421;
		NOU::sizeType r;

		r = static_cast<NOU::sizeType>((value % PRIME) % max);
		
		return r;
	}
}