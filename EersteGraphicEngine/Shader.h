#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"

namespace ege
{
    enum class ShaderFunction
    {
        FORWARD,
        DIFFUSE,
        DEPTH,
        SPECULAR,
        NORMAL,
        LIGHT,
        EFFECT
    };

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
        String Compiled;
        String VertexShaderPath;
        String HullShaderPath;
        String DomainShaderPath;
        String GeometryShaderPath;
        String PixelShaderPath;
        String ComputeShaderPath;
        String IncludeDirectory;

        ShaderConfig()
            : Compiled("false")
            , VertexShaderPath("")
            , HullShaderPath("")
            , DomainShaderPath("")
            , GeometryShaderPath("")
            , PixelShaderPath("")
            , ComputeShaderPath("")
            , IncludeDirectory("")
        {}
    };

    struct CompiledShader
    {
        size_t Size;
        char*  Data;
    };

    template <typename D3D11Shader>
    struct ShaderData
    {
        ShaderType     Type;
        D3D11Shader*   Shader;
        WString        Path;
        CompiledShader CompiledShader;

#if defined(EGE_WIN_SDK_8) || defined(EGE_WIN_SDK_10)
        ID3DBlob*      Blob;
#elif defined(EGE_WIN_SDK_7)
        ID3D10Blob*    Blob;
#endif

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
        void InsertConstantBuffer(UINT slot, ConstantBufferElement* constantBuffer);

    protected:
        HRESULT Open();
        HRESULT OpenVertexShader();
        HRESULT OpenHullShader();
        HRESULT OpenDomainShader();
        HRESULT OpenGeometryShader();
        HRESULT OpenPixelShader();
        HRESULT OpenComputeShader();
        HRESULT OpenShader(_In_ LPCWSTR srcFile, CompiledShader& compiledShader);

        HRESULT Compile();
        HRESULT CompileVertexShader();
        HRESULT CompileHullShader();
        HRESULT CompileDomainShader();
        HRESULT CompileGeometryShader();
        HRESULT CompilePixelShader();
        HRESULT CompileComputeShader();
        HRESULT CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob);

    protected:
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

        Map<UINT, ConstantBufferElement*> _constantBufferElements;
    };
}