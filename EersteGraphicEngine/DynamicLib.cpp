#include "DynamicLib.h"

namespace ege
{
    const char* DynamicLib::EXTENSION = "so";
    const char* DynamicLib::PREFIX = "lib";

    DynamicLib::DynamicLib(const String& name)
        : _name(name)
        , _handle(nullptr)
    {
        Load();
    }

    DynamicLib::~DynamicLib()
    {
    }

    void DynamicLib::Load()
    {
        if (_handle)
            return;

        _handle = (DYNAMIC_LIB_HANDLE)DYNAMIC_LIB_LOAD(_name.c_str());

        EGE_ASSERT_ERROR(_handle, "Could not load dynamic library " + _name + ".  System Error: " + DynamicLibError());
    }

    void DynamicLib::Unload()
    {
        if (!_handle)
            return;

        EGE_ASSERT_ERROR(DYNAMIC_LIB_UNLOAD(_handle), "Could not unload dynamic library " + _name + ".  System Error: " + DynamicLibError());
    }

    void* DynamicLib::GetSymbol(const String& strName) const
    {
        return nullptr;

        if (!_handle)
            return nullptr;

        return (void*)DYNAMIC_LIB_GETSYM(_handle, strName.c_str());
    }

    String DynamicLib::DynamicLibError()
    {
        LPVOID lpMsgBuf;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0,
            NULL
        );
        String ret = (char*)lpMsgBuf;
        // Free the buffer.
        LocalFree(lpMsgBuf);
        return ret;
    }
}