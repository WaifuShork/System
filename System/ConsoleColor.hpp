#pragma once

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
}
#endif