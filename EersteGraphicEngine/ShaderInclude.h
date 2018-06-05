#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class ShaderInclude : public ID3DInclude
    {
    public:
        ShaderInclude(const char* shaderDir, const char* systemDir);
        ~ShaderInclude();

        HRESULT __stdcall Open(
            D3D_INCLUDE_TYPE IncludeType,
            LPCSTR pFileName,
            LPCVOID pParentData,
            LPCVOID *ppData,
            UINT *pBytes);

        HRESULT __stdcall Close(LPCVOID pData);

    private:
        String GetFullPath(String relativePath);

    private:
        String _shaderDir;
        String _systemDir;
    };
}