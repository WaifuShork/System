#pragma once
#include <string>

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
	class ErrorMessages
	{
		public:
			static constexpr const char* InvalidNullPtrStringView = "error: invalid (const string_view&) [reason: nullptr]";
			static constexpr const char* CannotParseStringView = "error: cannot parse (const string_view&) to a valid character literal";
			static constexpr const char* IndexOutOfBounds = "error: index was greater than the total length of the (const string_view&)";
	};
}
#endif
