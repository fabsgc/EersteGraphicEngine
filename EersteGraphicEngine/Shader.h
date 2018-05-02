#pragma once

#include "PrerequisitesCore.h"
#include "D3D11RenderAPI.h"

namespace ege
{
    enum class ShaderType
    {
        VERTEX_SHADER,
        HULL_SHADER,
        DOMAIN_SHADER,
        GEOMETRY_SHADER,
        PIXEL_SHADER
    };

    template <typename D3D11Shader>
    struct ShaderData
    {
        ShaderType   Type;
#if defined(EGE_WIN_SDK_8) || defined(EGE_WIN_SDK_10)
        ID3DBlob*    Blob;
#elif defined(EGE_WIN_SDK_7)
        ID3D10Blob*  Blob;
#endif
        D3D11Shader* Shader;
        LPCWSTR      Path;

        ShaderData(ShaderType type)
            : Type(type)
            , Blob(nullptr)
            , Shader(nullptr)
            , Path(L"")
        {}
    };

    class Shader
    {
    public:
        Shader(String filePath);
        ~Shader();
        void Initialise();
        void Apply();
        bool HasShader(ShaderType type);

    public:
        static const D3D11_INPUT_ELEMENT_DESC VertexData[2];

    private:
        HRESULT Compile();
        HRESULT CompileVertexShader();
        HRESULT CompileHullShader();
        HRESULT CompileDomainShader();
        HRESULT CompileGeometryShader();
        HRESULT CompilePixelShader();
        HRESULT CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob);

    private:
        LPCWSTR                           _szFilePath;

        ShaderData<ID3D11VertexShader>    _vertexShader;
        ShaderData<ID3D11HullShader>      _hullShader;
        ShaderData<ID3D11DomainShader>    _domainShader;
        ShaderData<ID3D11GeometryShader>  _geometryShader;
        ShaderData<ID3D11PixelShader>     _pixelShader;

        ID3D11InputLayout*                _inputLayout;
    };
}