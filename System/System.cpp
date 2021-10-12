#include "Console.hpp"
#include "Float.hpp"
#include "Converter.hpp"

using namespace System;
int main()
{
	auto foo = Converter::ToUTF16("12.12e+27");
	Console::WriteLine(Float::TryParseF32(foo).value());

	return 0;
}