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
            finalPath = GetFullPath(_shaderDir) + "\\" + String(pFileName);
            break;
        case D3D_INCLUDE_SYSTEM: // #include <FILE>
            finalPath = GetFullPath(_systemDir) + "\\" + String(pFileName);
            break;
        default:
            assert(0);
        }

        std::ifstream includeFile(finalPath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

        if (includeFile.is_open())  
        {
            long long fileSize = includeFile.tellg();
            char* buf = new char[fileSize];
            includeFile.seekg(0, std::ios::beg);
            includeFile.read(buf, fileSize);
            includeFile.close();

            *ppData = buf;
            *pBytes = (UINT)fileSize;
        }
        else 
        {
            *ppData = nullptr;
            *pBytes = 0;

            return E_FAIL;
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