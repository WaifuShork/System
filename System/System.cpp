#include "Console.hpp"
#include "Float.hpp"

using namespace System;
int main()
{
	std::optional<Float64> result = Float::TryParseF64("12.12e+27");
	if (result.has_value())
	{
		Console::WriteLine(result.value());
	}

	return 0;
}