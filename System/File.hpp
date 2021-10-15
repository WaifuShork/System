#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>

#include "Char.hpp"
#include "Console.hpp"
#include "Integer.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class File
	{
		public:
			[[nodiscard]] static bool Exists(const std::wstring_view path)
			{
				return std::filesystem::exists(path);
			}

			[[nodiscard]] static std::optional<std::wstring> ReadAllText(const std::wstring_view path)
			{
				if (!Exists(path))
				{
					return {};
				}

				std::ifstream buffer(path);
				return std::wstring(std::istreambuf_iterator<Char8>(buffer), std::istreambuf_iterator<Char8>());
			}

			[[nodiscard]] static UInt64 CountLines(const std::wstring_view path)
			{
				if (!Exists(path))
				{
					Console::WriteLine(L"error: the file " + static_cast<std::wstring>(path.data()) + L" does not exit");
					return 0;
				}

				UInt64 lineCount = 0;
				std::ifstream i(path);
				std::string unused;
				while (std::getline(i, unused))
				{
					lineCount++;
				}

				return lineCount;
			}
	};
}
#endif