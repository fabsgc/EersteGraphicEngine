#include "ShaderInclude.h"

namespace ege
{
    ShaderInclude::ShaderInclude(const char* shaderDir, const char* systemDir)
        : _shaderDir(shaderDir)
        , _systemDir(systemDir)
    {
    }

    ShaderInclude::~ShaderInclude()
    {
    }

    HRESULT __stdcall ShaderInclude::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
    {
        String finalPath;
        switch (IncludeType)
        {
        case D3D_INCLUDE_LOCAL: // #include "FILE"
            finalPath = GetFullPath(_shaderDir);
            break;
        case D3D_INCLUDE_SYSTEM: // #include <FILE>
            finalPath = GetFullPath(_systemDir);
            break;
        default:
            assert(0);
        }

        std::ifstream fs;
        fs.open(finalPath.c_str(), std::ios::binary | std::ios::ate);
        fs.seekg(0, std::ios::end);
        UINT32 fileSize = (UINT32)fs.tellg();

        if (fileSize)
        {
            char* buf = new char[fileSize];
            fs.read(buf, fileSize);

            *ppData = buf;
            *pBytes = fileSize;
        }
        else
        {
            *ppData = nullptr;
            *pBytes = 0;
        }

        return S_OK;
    }

    HRESULT __stdcall ShaderInclude::Close(LPCVOID pData)
    {
        char* buf = (char*)pData;
        delete[] buf;
        return S_OK;
    }

    String ShaderInclude::GetFullPath(String relativePath)
    {
        DWORD  retval = 0;
        TCHAR  buffer[512] = TEXT("");
        TCHAR  buf[512]    = TEXT("");
        TCHAR** lppPart    = { NULL };
        WString relPath = ToWString(relativePath);

        retval = GetFullPathName(relPath.c_str(), 512, buffer, lppPart);
        EGE_ASSERT_ERROR((retval != 0), "GetFullPathName failed");

        WString finalPath(buffer);
        return ToString(finalPath);
    }
}