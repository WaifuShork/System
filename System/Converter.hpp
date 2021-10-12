#pragma once
#include <algorithm>
#include <codecvt>
#include <string>
#include "Char.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System::Converter
{
	[[nodiscard]] static std::u16string ToUTF16(const std::string& text)
	{
		return std::u16string(text.begin(), text.end());
	}

	[[nodiscard]] static std::string FromUTF16(const std::u16string& text)
	{
		return std::string(text.begin(), text.end());
	}

}
#endif