#pragma once

#if defined(_WIN64) || defined(_WIN32)
namespace System
{
    static constexpr wchar_t HighSurrogateStart = 0xd800;
    static constexpr wchar_t HighSurrogateEnd = 0xdbff;
    static constexpr wchar_t LowSurrogateStart = 0xdc00; 
    static constexpr wchar_t LowSurrogateEnd = 0xdfff; 

    static constexpr int_fast32_t UnicodeCategoryOffset = 0;
    static constexpr int_fast32_t BidiCategoryOffset = 1;
}
#endif