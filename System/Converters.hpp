#pragma once
#include <string>

#if defined(_WIN64) || defined(_WIN32)
namespace System::Converters
{
	[[nodiscard]] static const char* ConvertSToCCPtr(const std::string& text)
	{
		char* chrBuffer = new char[text.size() + 1];
		std::copy(text.begin(), text.end(), chrBuffer);
		chrBuffer[text.size()] = '\0';
		return chrBuffer;
	}

	[[nodiscard]] static const wchar_t* ConvertWSToCCPtr(const std::wstring& text)
	{
		wchar_t* chrBuffer = new wchar_t[text.size() + 1];
		std::copy(text.begin(), text.end(), chrBuffer);
		chrBuffer[text.size()] = '\0';
		return chrBuffer;
	}
}
#endif