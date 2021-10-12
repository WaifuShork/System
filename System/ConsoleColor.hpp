#pragma once

#include <string>
#include "Console.hpp"
#include <Windows.h>

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	enum class ConsoleColor
	{
		Black = 0,
		DarkBlue = 1,
		DarkGreen = 2,
		LightBlue = 3,
		DarkRed = 4,
		Magenta = 5,
		Orange = 6,
		LightGray = 7,
		Gray = 8,
		Blue = 9,
		Green = 10,
		Cyan = 11,
		Red = 12,
		Pink = 13,
		Yellow = 14,
		White = 15
	};

    [[nodiscard]] static std::string ForegroundColorCode(const ConsoleColor color)
    {
		switch (color)
		{
			case ConsoleColor::Black:     return "30"; // color_black      0
			case ConsoleColor::DarkBlue:  return "34"; // color_dark_blue  1
			case ConsoleColor::DarkGreen: return "32"; // color_dark_green 2
			case ConsoleColor::LightBlue: return "36"; // color_light_blue 3
			case ConsoleColor::DarkRed:   return "31"; // color_dark_red   4
			case ConsoleColor::Magenta:   return "35"; // color_magenta    5
			case ConsoleColor::Orange:    return "33"; // color_orange     6
			case ConsoleColor::LightGray: return "37"; // color_light_gray 7
			case ConsoleColor::Gray:      return "90"; // color_gray       8
			case ConsoleColor::Blue:      return "94"; // color_blue       9
			case ConsoleColor::Green:     return "92"; // color_green     10
			case ConsoleColor::Cyan:      return "96"; // color_cyan      11
			case ConsoleColor::Red:       return "91"; // color_red       12
			case ConsoleColor::Pink:      return "95"; // color_pink      13
			case ConsoleColor::Yellow:    return "93"; // color_yellow    14
			case ConsoleColor::White:     return "97"; // color_white     15
			default:					  return "37"; // NOLINT(clang-diagnostic-covered-switch-default)
		}
    }

    [[nodiscard]] static std::string BackgroundColorCode(const ConsoleColor color)
    {
		switch (color)
		{
			case ConsoleColor::Black:     return "40"; // color_black      0
			case ConsoleColor::DarkBlue:  return "44"; // color_dark_blue  1
			case ConsoleColor::DarkGreen: return "42"; // color_dark_green 2
			case ConsoleColor::LightBlue: return "46"; // color_light_blue 3
			case ConsoleColor::DarkRed:   return "41"; // color_dark_red   4
			case ConsoleColor::Magenta:   return "45"; // color_magenta    5
			case ConsoleColor::Orange:    return "43"; // color_orange     6
			case ConsoleColor::LightGray: return "47"; // color_light_gray 7
			case ConsoleColor::Gray:      return "100"; // color_gray       8
			case ConsoleColor::Blue:      return "104"; // color_blue       9
			case ConsoleColor::Green:     return "102"; // color_green     10
			case ConsoleColor::Cyan:      return "106"; // color_cyan      11
			case ConsoleColor::Red:       return "101"; // color_red       12
			case ConsoleColor::Pink:	  return "105"; // color_pink      13
			case ConsoleColor::Yellow:	  return "103"; // color_yellow    14
			case ConsoleColor::White:	  return "107"; // color_white     15
			default:					  return "40";  // NOLINT(clang-diagnostic-covered-switch-default)
		}
    }

	[[nodiscard]] static std::string IGetColor(const ConsoleColor fgColor)
    {
		return "\033[" + ForegroundColorCode(fgColor) + "m";
    }

	[[nodiscard]] static std::string IGetColor(const ConsoleColor fgColor, const ConsoleColor bgColor)
    {
		return "\033[" + ForegroundColorCode(fgColor) + ";" + BackgroundColorCode(bgColor) + "m";
    }

	static void ISetFGAndBGColor(const ConsoleColor fgColor, const ConsoleColor bgColor)
    {
		static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, static_cast<int>(bgColor) << 4 | static_cast<int>(fgColor));
    }
}
#endif