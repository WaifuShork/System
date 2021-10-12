#pragma once
#include <stdexcept>

#include "Float.hpp"
#include <vector>

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	enum class MidpointRounding
	{
		ToEven = 0,
		AwayFromZero = 1,
	};

	class MathF
	{
		private:
			static constexpr Float64 s_float64RoundLimit = 1e16;
			static constexpr Int32 s_maxRoundingDigits = 15;
			static inline std::vector<Float64> s_roundPower10Float6 = {
				1E0, 1E1, 1E2, 1E3, 1E4, 1E5, 1E6, 1E7, 1E8,
				1E9, 1E10, 1E11, 1E12, 1E13, 1E14, 1E15
			};

		public:
			static constexpr Float64 Pi = 3.14159265358979323846;
			static constexpr Float64 E = 2.7182818284590452354;
	};
}
#endif