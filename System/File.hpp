#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>
#include <chrono>

#include "Char.hpp"
#include "Integer.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class File
	{
		public:
			[[nodiscard]] static bool Exists(const std::u16string& path)
			{
				return std::filesystem::exists(path);
			}

			[[nodiscard]] static std::optional<std::u16string> ReadAllText(const std::u16string& path)
			{
				if (!Exists(path))
				{
					return {};
				}

				std::ifstream buffer(path);
				return std::u16string(std::istreambuf_iterator<Char8>(buffer), std::istreambuf_iterator<Char8>());
			}

			[[nodiscard]] static UInt64 CountLines(const std::u16string& path)
			{
				if (!Exists(path))
				{
					Console::WriteLine(u"The file " + path + u" does not exists");
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