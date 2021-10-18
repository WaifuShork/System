#pragma once
#include <optional>
#include <stdexcept>
#include <string>

#include "String.hpp"
#include "CharUnicodeInfo.hpp"
#include "Errors.hpp"

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
	[[nodiscard]] static constexpr WChar WCharMax()
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

	[[nodiscard]] static constexpr WChar WCharMin()
	{
		return 0;
	}
	
	// Primarily Char16 functions for unicode support
	class Char
	{
		public:
			[[nodiscard]] static std::wstring ToString(const Char8 value)
			{
				return std::wstring(1, value);
			}

			[[nodiscard]] static std::wstring ToString(const Char16 value)
			{
				return std::wstring(1, value);
			}

			[[nodiscard]] static std::wstring ToString(const Char32 value)
			{
				return std::wstring(1, static_cast<Char16>(value));
			}

			[[nodiscard]] static std::wstring ToString(const WChar value)
			{
				return std::wstring(1, value);
			}

			[[nodiscard]] static WChar Parse(const std::wstring_view& text)
			{
				if (text.data() == nullptr)
				{
					throw std::runtime_error(Errors::InvalidNullPtrStringView);
				}

				if (text.length() != 1)
				{
					throw std::runtime_error(Errors::CannotParseStringView);
				}
				
				return text[0];
			}

			[[nodiscard]] static std::optional<WChar> TryParse(const std::wstring_view& text)
			{
				if (text.data() == nullptr)
				{
					return {};
				}

				if (text.length() != 1)
				{
					return {};
				}

				return text[0];
			}


			[[nodiscard]] static bool IsLatin1(const WChar chr)
			{
				return (chr <= L'\x00ff');
			}

			[[nodiscard]] static bool IsAscii(const WChar chr)
			{
				return (chr <= L'\x007f');
			}

			[[nodiscard]] static bool IsAlpha(const WChar chr)
			{
				return (chr >= L'a' && chr <= L'z')
					|| (chr >= L'A' && chr <= L'Z');
			}

			[[nodiscard]] static bool IsLexicalIdentifier(const WChar chr)
			{
				return IsAlpha(chr) || chr == L'_';
			}

			[[nodiscard]] static bool IsDigit(const WChar chr)
			{
				if (IsLatin1(chr))
				{
					return chr >= L'0' && chr <= L'9';
				}

				return true;
			}

			[[nodiscard]] static bool IsWhiteSpace(const WChar chr)
			{
				// More information on where these definitions are located
				// https://en.wikipedia.org/wiki/Template:Whitespace_(Unicode)

				return chr == L'\u0009'  // horizontal tabulation (HT) '\t'
					|| chr == L'\u0020'  // space normal ASCII space ' ' 
					|| chr == L'\u00A0'  // no-break space
					|| chr == L'\u1680'  // ogham space mark
					|| chr == L'\u2000'  // en quad
					|| chr == L'\u2001'  // em quad
					|| chr == L'\u2002'  // en space
					|| chr == L'\u2003'  // em space
					|| chr == L'\u2004'  // three-per-em space
					|| chr == L'\u2005'  // four-per-em space
					|| chr == L'\u2006'  // six-per-em space
					|| chr == L'\u2007'  // figure space
					|| chr == L'\u2008'  // punctuation space
					|| chr == L'\u2009'  // thin space
					|| chr == L'\u200A'  // hair space
					|| chr == L'\u202F'  // narrow no-break space
					|| chr == L'\u205F'  // medium mathematical space
					|| chr == L'\u3000'; // ideographic space
			}

			[[nodiscard]] static bool IsNewLine(const WChar chr)
			{
				return chr == L'\u000A'  // line feed		    (LF) '\n'
					|| chr == L'\u000B'  // vertical tabulation (VT) '\v'
					|| chr == L'\u000C'  // form feed		    (FF) '\f'
					|| chr == L'\u000D'  // carriage return     (CR) '\r'
					|| chr == L'\u0085'  // next line	      (CR, LF) '\r\n'
					|| chr == L'\u2028'  // separator, line
					|| chr == L'\u2029'; // separator, paragraph
			}

			[[nodiscard]] static bool IsSurrogatePair(const WChar high, const WChar low)
			{
				return (high >= HighSurrogateStart && high <= HighSurrogateEnd)
				    && (low >= LowSurrogateStart && low <= LowSurrogateEnd);
			}

			[[nodiscard]] static bool IsHighSurrogate(const WChar chr)
			{
				return (chr >= HighSurrogateStart) && (chr <= HighSurrogateEnd);
			}

			[[nodiscard]] static bool IsHighSurrogate(const std::wstring_view& text, const size_t index)
			{
				if (String::IsNullOrEmpty(text))
				{
					throw std::runtime_error("");
				}
				if (index < 0 || index >= text.length())
				{
					throw std::runtime_error("");
				}

				return IsHighSurrogate(text[index]);
			}

			[[nodiscard]] static bool IsLowSurrogate(const WChar chr)
			{
				return (chr >= LowSurrogateStart) && (chr <= LowSurrogateEnd);
			}

			[[nodiscard]] static bool IsLowSurrogate(const std::wstring_view& text, const size_t index)
			{
				if (String::IsNullOrEmpty(text))
				{
					throw std::runtime_error(Errors::InvalidNullPtrStringView);
				}
				if (index < 0 || index >= text.length())
				{
					throw std::runtime_error(Errors::IndexOutOfBounds);
				}

				if (index + 1 < text.length())
				{
					return IsSurrogatePair(text[index], text[index + 1]);
				}

				return false;
			}
	};
}
#endif