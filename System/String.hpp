#pragma once
#include <algorithm>
#include <string_view>

#include "Char.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class String
	{
		public:
			[[nodiscard]] static bool IsNullOrEmpty(const std::wstring_view& text)
			{
				return (text.data() == nullptr || text.length() == 0);
			}

			[[nodiscard]] static bool IsNullOrWhiteSpace(const std::wstring_view& text)
			{
				if (text.data() == nullptr)
				{
					return true;
				}

				for (size_t i = 0; i < text.length(); i++)
				{
					if (!IsWhiteSpace(text, i))
					{
						return false;
					}
				}

				return true;
			}

			[[nodiscard]] static bool IsWhiteSpace(const std::wstring_view& text, const size_t index)
			{
				if (IsNullOrEmpty(text))
				{
					return false;
				}
				if (index > text.length() || index < 0)
				{
					return false;
				}
				
				// More information on where these definitions are located
				// https://en.wikipedia.org/wiki/Template:Whitespace_(Unicode)
				const wchar_t chr = text[index];
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

			[[nodiscard]] static bool IsNewLine(const std::wstring_view& text, const size_t index)
			{
				if (IsNullOrEmpty(text))
				{
					return false;
				}
				if (index > text.length() || index < 0)
				{
					return false;
				}

				// More information on where these definitions are located
				// https://en.wikipedia.org/wiki/Template:Whitespace_(Unicode)
				const wchar_t chr = text[index];
				return chr == L'\u000A'  // line feed		    (LF) '\n'
					|| chr == L'\u000B'  // vertical tabulation (VT) '\v'
					|| chr == L'\u000C'  // form feed		    (FF) '\f'
					|| chr == L'\u000D'  // carriage return     (CR) '\r'
					|| chr == L'\u0085'  // next line	      (CR, LF) '\r\n'
					|| chr == L'\u2028'  // separator, line
					|| chr == L'\u2029'; // separator, paragraph
			}
	};
}
#endif