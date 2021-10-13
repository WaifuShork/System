#pragma once

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	using Char8 = char;
	constexpr Char8 Char8Max = 0;
	constexpr Char8 Char8Min = static_cast<Char8>(255);

	using Char16 = char16_t;
	constexpr Char16 Char16Max = 0xFFFF;
	constexpr Char16 Char16Min = 0x00;

	using Char32 = char32_t;
	constexpr Char32 Char32Max = 0;
	constexpr Char32 Char32Min = 0;
	
	using WChar = wchar_t;
	static constexpr WChar WCharMax()
	{
		if constexpr (sizeof(WChar) == 2)
		{
			return 65535;
		}
		if constexpr (sizeof(WChar) == 4)
		{
			return 1114111;
		}
	}

	static constexpr WChar WCharMin()
	{
		return 0;
	}

	// Primarily Char16 functions for unicode support
	class Char
	{
		public:
			[[nodiscard]] static bool IsDigit(const WChar chr)
			{
				return chr >= '0' && chr <= '9';
			}

			[[nodiscard]] static bool IsWhiteSpace(const WChar chr)
			{
				return chr == ' '
					|| chr == '\t'
					|| chr == '\v'
					|| chr == '\f'
					|| chr == '\u00A0'
					|| chr == '\u001A';
			}

			[[nodiscard]] static bool IsAlpha(const WChar chr)
			{
				return (chr >= 'a' && chr <= 'z') ||
					   (chr >= 'A' && chr <= 'Z');
			}

			[[nodiscard]] static bool IsLexicalIdentifier(const WChar chr)
			{
				return IsAlpha(chr) || chr == '_';
			}

			[[nodiscard]] static bool IsNewLine(const WChar chr)
			{
				return chr == '\r'
					|| chr == '\n'
					|| chr == '\u0085';
			}
	};
}
#endif