#include "Console.hpp"
#include "File.hpp"

using namespace System;
int main()
{
	auto lines = File::CountLines(u"vsharp.txt");
	Console::WriteLine(lines);
	// auto foo = Converter::ToUTF16("12.12e+27");
	// Console::WriteLine(Float::TryParseF32(foo).value());
	return 0;
}