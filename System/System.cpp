#include "Console.hpp"

using namespace System;
int main()
{
	Console::SetForegroundColor(ConsoleColor::Red);
	Console::WriteLine("Hello world");
	Console::ResetColor();
	Console::WriteLine("uwu");
	return 0;
}