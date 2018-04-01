#include "nostrautils/dat_alg/Hashing.hpp"

namespace NOU::NOU_DAT_ALG
{
	NOU_FUNC NOU::sizeType hashValue(NOU::sizeType value, NOU::sizeType max) 
	{
		NOU_COND_PUSH_ERROR((max < 1), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Value max cannot be below 1");

		const NOU::int16 PRIME = 421;
		NOU::sizeType r;

		r = static_cast<NOU::sizeType>((value % PRIME) % max);
		
		return r;
	}
}