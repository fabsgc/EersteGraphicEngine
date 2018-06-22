#pragma once

#include "PrerequisitesUtil.h"

namespace ege
{
    /* ###################################################################
    *  ############# STRING TYPES ########################################
    *  ################################################################ */

    template <typename T>
    using BasicString = std::basic_string <T, std::char_traits<T>, StdAllocator<T, BasicAllocator>>;

    /**	\brief Basic string stream that uses Banshee memory allocators. */
    template <typename T>
    using BasicStringStream = std::basic_stringstream <T, std::char_traits<T>, StdAllocator<T, BasicAllocator>>;

    /** \brief Wide string used primarily for handling Unicode text (UTF-32 on Linux, UTF-16 on Windows, generally). */
    typedef BasicString<wchar_t> WString;

    /** \brief Narrow string used for handling narrow encoded text (either locale specific ANSI or UTF-8). */
    typedef BasicString<char> String;

    /** \brief IStringStream wrapper */
    template <typename T>
    using BasicIStringStream = std::basic_istringstream<T, std::char_traits<T>, StdAllocator<T, BasicAllocator>>;

    typedef BasicIStringStream<char> IStringStream;

    /** \brief Wide string used UTF-16 encoded strings. */
    typedef BasicString<char16_t> U16String;

    /** \brief Wide string used UTF-32 encoded strings. */
    typedef BasicString<char32_t> U32String;

    /** \brief Wide string stream used for primarily for constructing wide strings. */
    typedef BasicStringStream<wchar_t> WStringStream;

    /** \brief Wide string stream used for primarily for constructing narrow strings. */
    typedef BasicStringStream<char> StringStream;

    /** \brief Wide string stream used for primarily for constructing UTF-16 strings. */
    typedef BasicStringStream<char16_t> U16StringStream;

    /** \brief Wide string stream used for primarily for constructing UTF-32 strings. */
    typedef BasicStringStream<char32_t> U32StringStream;

    /* ###################################################################
    *  ############# STRING CONVERSION FUNCTIONS #########################
    *  ################################################################ */

    /** \brief Converts a narrow string to a wide string. */
    WString ToWString(const String& source);

    /**	\brief Converts a narrow string to a wide string. */
    WString ToWString(const char* source);

    /** \brief Converts a float to a string. */
    WString ToWString(float val, unsigned short precision = 6, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /** \brief Converts a double to a string. */
    WString ToWString(double val, unsigned short precision = 6, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an int to a string. */
    WString ToWString(int val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an unsigned int to a string. */
    WString ToWString(unsigned int val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an 64bit integer to a string. */
    WString ToWString(INT64 val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an 64bit unsigned to a string. */
    WString ToWString(UINT64 val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an narrow char unsigned to a string. */
    WString ToWString(char val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an wide bit char unsigned to a string. */
    WString ToWString(wchar_t val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /** \brief Converts a wide string to a narrow string. */
    String ToString(const WString& source);

    /**	\brief Converts a wide string to a narrow string. */
    String ToString(const wchar_t* source);

    /**	\brief Converts a float to a string. */
    String ToString(float val, unsigned short precision = 6, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts a double to a string. */
    String ToString(double val, unsigned short precision = 6, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    String ToString(int val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an unsigned int to a string. */
    String ToString(unsigned int val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts a 64bit int to a string. */
    String ToString(INT64 val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**	\brief Converts an 64bit unsigned int to a string. */
    String ToString(UINT64 val, unsigned short width = 0, char fill = ' ', std::ios::fmtflags flags = std::ios::fmtflags(0));

    /**
    * \brief Converts a String to a float.
    * \note	0.0f if the value could not be parsed, otherwise the numeric version of the string.
    */
    float ParseFloat(const String& val, float defaultValue = 0);

    /**
    * \brief Converts a String to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    INT32 ParseINT32(const String& val, INT32 defaultValue = 0);

    /**
    * \brief Converts a String to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    UINT32 ParseUINT32(const String& val, UINT32 defaultValue = 0);

    /**
    * \brief Converts a String to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    INT64 ParseINT64(const String& val, INT64 defaultValue = 0);

    /**
    * \brief Converts a String to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    UINT64 ParseUINT64(const String& val, UINT64 defaultValue = 0);

    /** \brief Checks the String is a valid number value. */
    bool IsNumber(const String& val);

    /**
    * \brief Converts a WString to a float.
    * \note	0.0f if the value could not be parsed, otherwise the numeric version of the string.
    */
    float ParseFloat(const WString& val, float defaultValue = 0);

    /**
    * \brief Converts a WString to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    INT32 ParseINT32(const WString& val, INT32 defaultValue = 0);

    /**
    * \brief Converts a WString to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    UINT32 ParseUINT32(const WString& val, UINT32 defaultValue = 0);

    /**
    * \brief Converts a WString to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    INT64 ParseINT64(const WString& val, INT64 defaultValue = 0);

    /**
    * \brief Converts a WString to a whole number.
    * \note	0 if the value could not be parsed, otherwise the numeric version of the string.
    */
    UINT64 ParseUINT64(const WString& val, UINT64 defaultValue = 0);

    /**
    * \brief Checks the WString is a valid number value.
    */
    bool IsNumber(const WString& val);

    /**
    * \brief Split string according to delimiter
    */
    Vector<String> Split(const String& s, char delimiter);
}