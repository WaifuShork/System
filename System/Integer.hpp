#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include "fast_float.h"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	// -128 to 127
	using Int8 = int_fast8_t;
	constexpr Int8 Int8Max = 0x7Fi8;
	constexpr Int8 Int8Min = 0x80i8;

	// 0 to 255
	using UInt8 = uint_fast8_t;
	constexpr UInt8 UInt8Max = 0xFFui8;
	constexpr UInt8 UInt8Min = 0ui8;

	// -32768 to 32767
	using Int16 = int_fast16_t;
	constexpr Int16 Int16Max = 0x7FFFi16;
	constexpr Int16 Int16Min = 0x8000i16;

	// 0 to 65535
	using UInt16 = uint_fast16_t;
	constexpr UInt16 UInt16Max = 0xFFFFui16;
	constexpr UInt16 UInt16Min = 0ui16;

	// -2,147,483,648 to 2,147,483,647
	using Int32 = int_fast32_t;
	constexpr Int32 Int32Max = 0x7fffffffi32;
	constexpr Int32 Int32Min = 0x80000000i32;

	// 0 to 4,294,967,295
	using UInt32 = uint_fast32_t;
	constexpr UInt32 UInt32Max = 0xffffffffui32;
	constexpr UInt32 UInt32Min = 0ui32;

	// -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
	using Int64 = int_fast64_t;
	constexpr Int64 Int64Max = 0x7fffffffffffffffi64;
	constexpr Int64 Int64Min = 0x8000000000000000i64;

	// 0 to 18,446,744,073,709,551,615
	using UInt64 = uint_fast64_t;
	constexpr UInt64 UInt64Max = 0xffffffffffffffffi64;
	constexpr UInt64 UInt64Min = 0x0ui64;

	class Integer
	{
		public:
			[[nodiscard]] static std::optional<Int64> TryParseI64(const std::wstring_view& value)
			{
				if (value.length() == 0)
				{
					return {};
				}

				bool isNeg = false;
				Int64 result = 0;

				for (size_t i = 0; i < value.length(); i++)
				{
					const wchar_t ch = value[i];
					if (i == 0 && ch == '-')
					{
						isNeg = true;
						continue;
					}
					if (ch >= '0' && ch <= '9')
					{
						result *= 10;
						result += ch - '0'; // TODO: possible overflow fixing
					}
					else
					{
						return {};
					}
				}

				return isNeg ? -result : result;
			}

			[[nodiscard]] static std::optional<UInt64> TryParseUI64(const std::wstring_view& value)
			{
				if (value.length() == 0)
				{
					return {};
				}

				UInt64 result = 0;
				for (size_t i = 0; i < value.length(); i++)
				{
					const wchar_t c = value[i];
					if ((i == 0) && (c == '-'))
					{
						return {};
					}
					if ((c >= '0') && (c <= '9'))
					{
						result *= 10;
						result += c - '0';
					}
					else
					{
						return {};
					}
				}
				return result;
			}

			[[nodiscard]]static std::optional<Int32> TryParseI32(const std::wstring_view& value)
			{
				if (value.length() == 0)
				{
					return {};
				}

				bool isNeg = false;
				Int32 result = 0;

				for (size_t i = 0; i < value.length(); i++)
				{
					const wchar_t ch = value[i];
					if (i == 0 && ch == '-')
					{
						isNeg = true;
						continue;
					}
					if (ch >= '0' && ch <= '9')
					{
						result *= 10;
						result += ch - 'A' + 10;
					}
					else
					{
						return {};
					}
				}

				return isNeg ? -result : result;
			}

			[[nodiscard]] static std::optional<UInt32> TryParseUI32(const std::wstring_view& value)
			{
				if (value.length() == 0)
				{
					return {};
				}

				UInt32 result = 0;
				for (size_t i = 0; i < value.length(); i++)
				{
					const wchar_t ch = value[i];
					if (i == 0 && ch == '-')
					{
						return {};
					}
					if (ch >= '0' && ch <= '9')
					{
						result *= 10;
						result += static_cast<UInt32>(ch - '0');
					}
					else
					{
						return {};
					}
				}
				return result;
			}

			[[nodiscard]] static std::optional<Int16> TryParseI16(const std::wstring_view& value)
			{
				return TryParseI32(value);
			}

			[[nodiscard]] static std::optional<UInt16> TryParseUI16(const std::wstring_view& value)
			{
				return TryParseUI32(value);
			}

			[[nodiscard]] static std::optional<Int8> TryParseI8(const std::wstring_view& value)
			{
				return TryParseI32(value);
			}

			[[nodiscard]] static std::optional<UInt8> TryParseUI8(const std::wstring_view& value)
			{
				return TryParseUI32(value);
			}
	};
}
#endif 