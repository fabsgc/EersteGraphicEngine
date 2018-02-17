#pragma once

#include "PrerequisitesUtil.h"
#include "MemoryAllocator.h"

namespace ege
{
    template <typename T>
    using BasicString = std::basic_string <T, std::char_traits<T>, StdAllocator<T, BasicAllocator>>;

    /**	Basic string stream that uses Banshee memory allocators. */
    template <typename T>
    using BasicStringStream = std::basic_stringstream <T, std::char_traits<T>, StdAllocator<T, BasicAllocator>>;

    /** Wide string used primarily for handling Unicode text (UTF-32 on Linux, UTF-16 on Windows, generally). */
    typedef BasicString<wchar_t> WString;

    /** Narrow string used for handling narrow encoded text (either locale specific ANSI or UTF-8). */
    typedef BasicString<char> String;

    /** Wide string used UTF-16 encoded strings. */
    typedef BasicString<char16_t> U16String;

    /** Wide string used UTF-32 encoded strings. */
    typedef BasicString<char32_t> U32String;

    /** Wide string stream used for primarily for constructing wide strings. */
    typedef BasicStringStream<wchar_t> WStringStream;

    /** Wide string stream used for primarily for constructing narrow strings. */
    typedef BasicStringStream<char> StringStream;

    /** Wide string stream used for primarily for constructing UTF-16 strings. */
    typedef BasicStringStream<char16_t> U16StringStream;

    /** Wide string stream used for primarily for constructing UTF-32 strings. */
    typedef BasicStringStream<char32_t> U32StringStream;

    WString Str2WStr(const String& s);
}