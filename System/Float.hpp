#pragma once
#include <codecvt>
#include <optional>
#include <string>

#include "Char.hpp"
#include "Converters.hpp"
#include "fast_float.h"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	using Float32 = float;
	constexpr Float32 Float32Min = -3.40282346638528859e+38f;
	constexpr Float32 Float32Max = 3.40282346638528859e+38;

	using Float64 = double;
	constexpr Float64 Float64Min = -1.7976931348623157E+308;
	constexpr Float64 Float64Max = 1.7976931348623157E+308;

	// using Float128 = long double;
	// it's physically impossible to type this in a single number in C++ so I'll need to figure something out... 
	// constexpr Float128 Float128Max = 1.18973149535723176508575932662800702e+4932;
	// constexpr Float128 Float128Min = 3.36210314311209350626267781732175260e-4932;

	class Float
	{
		public:
			[[nodiscard]] static std::optional<Float64> TryParseF64(const std::u16string& text)
			{
				Float64 result;

				const std::string strText = Converters::ConvertToString(text);
				const Char8* first = strText.data();
				const Char8* last = strText.data() + text.size();

				// ReSharper disable once CppTooWideScopeInitStatement
				const auto [discarded, ec] = fast_float::from_chars(first, last, result);

				// The parsing failed
				if (ec != std::errc())
				{
					return {};
				}

				return result;
			}

			[[nodiscard]] static std::optional<Float32> TryParseF32(const std::u16string& text)
			{
				Float32 result;

				const std::string strText = Converters::ConvertToString(text);
				const Char8* first = strText.data();
				const Char8* last = strText.data() + text.size();

				// ReSharper disable once CppTooWideScopeInitStatement
				const auto [discarded, errorCode] = fast_float::from_chars(first, last, result);

				// The parsing failed
				if (errorCode != std::errc())
				{
					return {};
				}

				return result;
			}

			[[nodiscard]] static std::optional<Float64> TryParseF64(const std::string& text)
			{
				Float64 result;

				const Char8* first = text.data();
				const Char8* last = text.data() + text.size();

				// ReSharper disable once CppTooWideScopeInitStatement
				const auto [discarded, ec] = fast_float::from_chars(first, last, result);

				// The parsing failed
				if (ec != std::errc())
				{
					return {};
				}

				return result;
			}

			[[nodiscard]] static std::optional<Float32> TryParseF32(const std::string& text)
			{
				Float32 result;

				const Char8* first = text.data();
				const Char8* last = text.data() + text.size();

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