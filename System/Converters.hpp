#pragma once
#include <algorithm>
#include <codecvt>
#include <string>
#include "Char.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System::Converters
{
	[[nodiscard]] static const Char8* ConvertToCharPtr(const std::string& text)
	{
		Char8* chrBuffer = new Char8[text.size() + 1];
		std::copy(text.begin(), text.end(), chrBuffer);
		chrBuffer[text.size()] = '\0';
		return chrBuffer;
	}

	[[nodiscard]] static const WChar* ConvertToCharPtr(const std::wstring& text)
	{
		WChar* chrBuffer = new WChar[text.size() + 1];
		std::copy(text.begin(), text.end(), chrBuffer);
		chrBuffer[text.size()] = '\0';
		return chrBuffer;
	}

	[[nodiscard]] static std::string ConvertToString(const std::wstring& text)
	{
		std::string buffer;
		std::transform(text.begin(), text.end(), std::back_inserter(buffer), [](const WChar chr)
		{
			return static_cast<Char8>(chr);
		});

		return buffer;
	}

	[[nodiscard]] static std::wstring ConvertToWString(const std::string& text)
	{
		std::wstring buffer; 
		for (const Char8 chr : text)
		{
			buffer += chr;
		}

		return buffer;
	}

	[[nodiscard]] static std::string ConvertToString(const std::u16string& text)
	{
		std::string buffer;
		for (const Char16 chr : text)
		{
			buffer += static_cast<Char8>(chr);
		}

		return buffer;
	}
}
#endif