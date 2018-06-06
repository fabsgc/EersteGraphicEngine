#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"

namespace ege
{
    enum class ShaderType
    {
        VERTEX_SHADER,
        HULL_SHADER,
        DOMAIN_SHADER,
        GEOMETRY_SHADER,
        PIXEL_SHADER,
        COMPUTE_SHADER
    };

    struct ShaderConfig
    {
        String Name;
        String VertexShaderPath;
        String HullShaderPath;
        String DomainShaderPath;
        String GeometryShaderPath;
        String PixelShaderPath;
        String ComputeShaderPath;
        String IncludeDirectory;

        ShaderConfig()
            : VertexShaderPath("")
            , HullShaderPath("")
            , DomainShaderPath("")
            , GeometryShaderPath("")
            , PixelShaderPath("")
            , ComputeShaderPath("")
            , IncludeDirectory("")
        {}
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
        WString      Path;

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
        Shader(ShaderConfig config);
        Shader(ShaderConfig config, Vector<D3D11_INPUT_ELEMENT_DESC>& inputElementsDesc);
        ~Shader();
        void Initialise();
        void Apply();
        bool HasShader(ShaderType type);

    public:
        static Vector<D3D11_INPUT_ELEMENT_DESC> VertexElementDesc;

    private:
        HRESULT Compile();
        HRESULT CompileVertexShader();
        HRESULT CompileHullShader();
        HRESULT CompileDomainShader();
        HRESULT CompileGeometryShader();
        HRESULT CompilePixelShader();
        HRESULT CompileComputeShader();
        HRESULT CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob);

    private:
        ShaderConfig                      _config;

        ShaderData<ID3D11VertexShader>    _vertexShader;
        ShaderData<ID3D11HullShader>      _hullShader;
        ShaderData<ID3D11DomainShader>    _domainShader;
        ShaderData<ID3D11GeometryShader>  _geometryShader;
        ShaderData<ID3D11PixelShader>     _pixelShader;
        ShaderData<ID3D11ComputeShader>   _computeShader;

        D3D11_INPUT_ELEMENT_DESC*         _inputElementsDesc;
        UINT32                            _numberElementsDesc;

        ID3D11InputLayout*                _inputLayout;
    };
}