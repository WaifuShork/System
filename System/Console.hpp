#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <sstream>

#include "ConsoleColor.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class Console
	{
		public:
			static void SetTitle(const std::wstring_view& title)
			{
				SetConsoleTitleW(title.data());
			}

			static ConsoleColor GetForegroundColor()
			{
				CONSOLE_SCREEN_BUFFER_INFO info;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
				return static_cast<ConsoleColor>(info.wAttributes);
			}

			static void SetForegroundColor(const ConsoleColor fgColor)
			{
				static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, static_cast<WORD>(fgColor));
			}

			static void ResetColor()
			{
				static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, static_cast<int>(ConsoleColor::White));
			}

			static void Clear()
			{
				const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // NOLINT(misc-misplaced-const)
				if (hStdOut == INVALID_HANDLE_VALUE)
				{
					return;
				}

				CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo;
				if (!GetConsoleScreenBufferInfo(hStdOut, &consoleBufferInfo))
				{
					return;
				}

				DWORD count;
				constexpr COORD homeCoords = { 0, 0 };
				const DWORD cellCount = consoleBufferInfo.dwSize.X * consoleBufferInfo.dwSize.Y;
				if (!FillConsoleOutputCharacter(hStdOut, static_cast<TCHAR>(' '), cellCount, homeCoords, &count))
				{
					return;
				}

				if (!FillConsoleOutputAttribute(hStdOut, consoleBufferInfo.wAttributes, cellCount, homeCoords, &count))
				{
					return;
				}
				
				SetConsoleCursorPosition(hStdOut, homeCoords);
			}

			static std::wstring ReadLine()
			{
				std::wstring buffer{};
				std::getline(std::wcin, buffer);
				return buffer;
			}

			static std::wstring ReadWord()
			{
				std::wstring buffer{};
				std::wcin >> buffer;
				return buffer;
			}

			static void Write(const std::wstring_view& input = L"")
			{
				std::wcout << input;
			}

			static void WriteLine(const std::wstring_view& input = L"")
			{
				std::wcout << input << '\n';
			}

			static void WriteError(const std::wstring_view& input)
			{
				SetForegroundColor(ConsoleColor::DarkRed);
				Write(input);
				ResetColor();
			}

			static void WriteErrorLine(const std::wstring_view& input)
			{
				SetForegroundColor(ConsoleColor::DarkRed);
				WriteLine(input);
				ResetColor();
			}
	};
}
#endif