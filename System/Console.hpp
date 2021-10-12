#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <tuple>
#include <conio.h>

#include "ConsoleColor.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class Console
	{
		public:
			static void SetTitleW(const std::wstring& title)
			{
				SetConsoleTitleW(title.c_str());
			}

			static void SetTitle(const std::string& title)
			{
				SetConsoleTitleA(title.c_str());
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

			static std::tuple<int, int> GetCursorPosition()
			{
				return std::make_tuple(0, 0);
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

			static std::string ReadLine()
			{
				std::string buffer{};
				std::getline(std::cin, buffer);
				return buffer;
			}

			static std::wstring ReadLineW()
			{
				std::wstring buffer{};
				std::getline(std::wcin, buffer);
				return buffer;
			}

			static std::wstring ReadWordW()
			{
				std::wstring buffer{};
				std::wcin >> buffer;
				return buffer;
			}

			static void WriteLine(const std::string& input = "")
			{
				std::cout << input << '\n';
			}

			static void WriteLineW(const std::wstring& input = L"")
			{
				std::wcout << input << '\n';
			}
	};
}
#endif