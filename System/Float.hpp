#pragma once
#include <optional>
#include <string>

#include "Char.hpp"
#include "Convert.hpp"
#include "fast_float.h"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	using Float32 = float;
	constexpr Float32 Float32Min = 1.175494351e-38F;
	constexpr Float32 Float32Max = 3.402823466e+38F;
	constexpr Float32 Float32Epsilon = 1.192092896e-07F;

	using Float64 = double;
	constexpr Float64 Float64Min = 2.2250738585072014e-308;
	constexpr Float64 Float64Max = 1.7976931348623158e+308;
	constexpr Float64 Float64Epsilon = 2.2204460492503131e-016;

	class Float
	{
		public:
			[[nodiscard]] static std::optional<Float64> TryParseF64(const std::wstring_view text)
			{
				Float64 result;
				
				const std::string strBuffer = Convert::ToString(text);
				const Char8* first = strBuffer.data();
				const Char8* last = strBuffer.data() + strBuffer.size();

				// ReSharper disable once CppTooWideScopeInitStatement
				const auto [discarded, ec] = fast_float::from_chars(first, last, result);

				// The parsing failed
				if (ec != std::errc())
				{
					return {};
				}

				return result;
			}

			[[nodiscard]] static std::optional<Float32> TryParseF32(const std::wstring_view text)
			{
				Float32 result;

				const std::string strBuffer = Convert::ToString(text);
				const Char8* first = strBuffer.data();
				const Char8* last = strBuffer.data() + strBuffer.size();

				// ReSharper disable once CppTooWideScopeInitStatement
				const auto [discarded, errorCode] = fast_float::from_chars(first, last, result);

				// The parsing failed
				if (errorCode != std::errc())
				{
					return {};
				}

				return result;
			}
	};
}
#endif