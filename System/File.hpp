#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>

#include "Char.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class File
	{
		public:
			[[nodiscard]] static bool Exists(const std::string& path)
			{
				return std::filesystem::exists(path);
			}


			[[nodiscard]] static std::optional<std::string> ReadAllText(const std::string& path)
			{
				if (!Exists(path))
				{
					return {};
				}

				std::ifstream buffer(path);
				return std::string(std::istreambuf_iterator<Char8>(buffer), std::istreambuf_iterator<Char8>());
			}
	};
}
#endif