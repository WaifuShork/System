#pragma once
#include "Char.hpp"

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
    static constexpr wchar_t HighSurrogateStart = 0xd800;
    static constexpr wchar_t HighSurrogateEnd = 0xdbff;
    static constexpr wchar_t LowSurrogateStart = 0xdc00; 
    static constexpr wchar_t LowSurrogateEnd = 0xdfff; 

    static constexpr Int32 UnicodeCategoryOffset = 0;
    static constexpr Int32 BidiCategoryOffset = 1;
}
#endif