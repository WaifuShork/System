#pragma once
#include <ios>

#if defined(_WIN64) || defined(_WIN32)
namespace System::Convert
{
	[[nodiscard]] static std::string ToString(const std::wstring_view& text)
	{
		return std::string(text.begin(), text.end());
	}

	[[nodiscard]] static std::wstring ToWString(const std::string_view& text)
	{
		return std::wstring(text.begin(), text.end());
	}
}
#endif