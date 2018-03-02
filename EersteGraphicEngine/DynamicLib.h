#pragma once

#include "PrerequisitesUtil.h"

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

namespace ege
{
#define DYNAMIC_LIB_HANDLE hInstance
#define DYNAMIC_LIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#define DYNAMIC_LIB_GETSYM( a, b ) GetProcAddress( a, b )
#define DYNAMIC_LIB_UNLOAD( a ) !FreeLibrary( a )

    class DynamicLib
    {
    public:
        DynamicLib(const String& name);
        ~DynamicLib();

        void  Load();
        void  Unload();
        const String& getName() const { return _name; }
        void* GetSymbol(const String& strName) const;

    public:
        static const char* EXTENSION;
        static const char* PREFIX;

    protected:
        String DynamicLibError();

    protected:
        String             _name;
        DYNAMIC_LIB_HANDLE _handle;
    };
}