#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <tuple>
#include <conio.h>

#include "ConsoleColor.hpp"
#include "Converter.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class Console
	{
		public:
			static void SetTitle(const std::u16string& title)
			{
				SetConsoleTitleA(Converter::FromUTF16(title).c_str());
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

			static std::u16string ReadLine()
			{
				std::wstring buffer{};
				std::getline(std::wcin, buffer);
				return std::u16string(buffer.begin(), buffer.end());
			}

			static std::u16string ReadWord()
			{
				std::wstring buffer{};
				std::wcin >> buffer;
				return std::u16string(buffer.begin(), buffer.end());
				// return Converter::U16Converter.from_bytes(buffer);
			}
			
			static void WriteLine(const std::u16string& input = u"")
			{
				std::cout << Converter::FromUTF16(input) << '\n';
			}

			template<typename T>
			static void WriteLine(const T& input = "")
			{
				std::cout << input << '\n';
			}
	};
}
#endif