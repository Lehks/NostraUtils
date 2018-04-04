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

	NOU_FUNC MD5Hash md5(const NOU::byte *input, sizeType size)
	{
		Vector<byte> bytes(10);


		//specifies the per - round shift amounts
		uint32 s[64] = {
			7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
			5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
			6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

		//floor(abs(sin(i + 1)) × 2^32) for i in {0..63}
		uint32 sin[64] = {
			0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
			0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
			0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
			0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
			0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
			0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
			0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
			0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
			0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
			0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
			0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
			0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
			0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
			0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
			0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

		//predefined constants
		uint32 a0 = 0x67452301;
		uint32 b0 = 0xefcdab89;
		uint32 c0 = 0x98badcfe;
		uint32 d0 = 0x10325476;

		//bitlength of input
		sizeType len;
		for (len = 0; len < size; len++)
		{
			bytes.emplaceBack(input[len]);
		}

		bytes.emplaceBack(128);

		//bitlength of input appended by 0b00000000 and appended until newLength congruent 56 % 64
		sizeType secondLen;
		for (secondLen = len + 1; ((secondLen - 56) % 64) != 0; secondLen++)
		{
			bytes.emplaceBack();
		}

		sizeType finalLen = 0;		//length after appending 0b10000000 and multiple 0b00000000's and appending len as 64-bit little endian
		finalLen += 8;

		//writing length as little endian
		byte *pEndian = reinterpret_cast<byte*>(&len);


		for (sizeType i = 0; i < 8; i++)
		{
			bytes.emplaceBack(pEndian[8 - i - 1]);
		}



		//64-byte blockwise operations
		// Vector<byte64> blocks;
		sizeType bnp;		//Block null position
		sizeType cp;		//chunk position
		int32 chunk[16];

		uint32 a;
		uint32 b;
		uint32 c;
		uint32 d;

		uint32 tmp, tmp1;

		uint32 f, g;

		for (sizeType z = 0; z < bytes.size() / 64; z++)
		{
			bnp = z * 64;
			for (sizeType i = 0; i < 16; i++)
			{
				chunk[i] = *reinterpret_cast<uint32*>(bytes.data() + bnp + i * 4);
			}

			a = a0;
			b = b0;
			c = c0;
			d = d0;

			//Main loop

			for (sizeType i = 0; i < 64; i++)
			{
				if (0 <= i && i < 16)
				{
					f = (b & c) | (!b & d);
					g = i;
				} else if (16 <= i && i < 32)
				{
					f = (b & d) | (c & !d);
					g = (5 * i + 1) % 16;
				} else if (32 <= i && i < 48)
				{
					f = NOU_XOR(NOU_XOR(b, c), d);
					g = (3 * i + 5) % 16;
				} else if (48 <= i && i < 64)
				{
					f = NOU_XOR(c, (b | !d));
					g = (7 * i) % 16;
				}

				tmp = d;
				d = c;
				c = b;
				tmp1 = chunk[g];
				tmp1 += a;
				tmp1 += f;
				tmp1 += sin[i];

				b = +leftRotation(tmp1, s[i]);
				a = tmp;
			}

			a0 += a;
			b0 += b;
			c0 += c;
			d0 += d;




		}

		MD5Hash ret;

		*reinterpret_cast<uint32*>(ret.data() + 0) = a0;
		*reinterpret_cast<uint32*>(ret.data() + 4) = b0;
		*reinterpret_cast<uint32*>(ret.data() + 8) = c0;
		*reinterpret_cast<uint32*>(ret.data() + 12) = d0;
		return ret;
	}

	NOU_FUNC byte leftRotation(const byte input, int32 rotations)
	{
		byte r = input;
		const byte b = 0b10000000;

		rotations = rotations % 8;
		byte c;
		for (sizeType i = 0; i < rotations; i++)
		{
			c = b & r;
			if (c != 0)
			{
				r <<= 1;
				r++;
			} else
			{
				r <<= 1;
			}
		}
		return r;
	}
}