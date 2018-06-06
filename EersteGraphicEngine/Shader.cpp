#include "Shader.h"
#include "ShaderInclude.h"

namespace ege
{
    Vector<D3D11_INPUT_ELEMENT_DESC> Shader::VertexElementDesc =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "BINORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    Shader::Shader(ShaderConfig config)
        : Shader(config, VertexElementDesc)
    {}

    Shader::Shader(ShaderConfig config, Vector<D3D11_INPUT_ELEMENT_DESC>& inputElementsDesc)
        : _config(config)
        , _vertexShader(ShaderType::VERTEX_SHADER)
        , _hullShader(ShaderType::HULL_SHADER)
        , _domainShader(ShaderType::DOMAIN_SHADER)
        , _geometryShader(ShaderType::GEOMETRY_SHADER)
        , _pixelShader(ShaderType::PIXEL_SHADER)
        , _computeShader(ShaderType::COMPUTE_SHADER)
        , _inputLayout(nullptr)
        , _inputElementsDesc(&inputElementsDesc[0])
        , _numberElementsDesc((UINT32)inputElementsDesc.size())
    {}

    Shader::~Shader()
    {
        SafeReleaseCom(_vertexShader.Shader);
        SafeReleaseCom(_hullShader.Shader);
        SafeReleaseCom(_domainShader.Shader);
        SafeReleaseCom(_geometryShader.Shader);
        SafeReleaseCom(_pixelShader.Shader);
        SafeReleaseCom(_computeShader.Shader);
        SafeReleaseCom(_inputLayout);
    }

    void Shader::Initialise()
    {
        _vertexShader.Path   = ToWString(_config.VertexShaderPath);
        _hullShader.Path     = ToWString(_config.HullShaderPath);
        _domainShader.Path   = ToWString(_config.DomainShaderPath);
        _geometryShader.Path = ToWString(_config.GeometryShaderPath);
        _pixelShader.Path    = ToWString(_config.PixelShaderPath);
        _computeShader.Path  = ToWString(_config.ComputeShaderPath);

        if (!HasShader(ShaderType::VERTEX_SHADER) || !HasShader(ShaderType::PIXEL_SHADER))
        {
            EGE_ASSERT_ERROR(false, "Shader object must have at least one vertex shader and one pixel shader");
        }

        HRESULT hr = Compile();
        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't compile shader");
    }

    void Shader::Apply()
    {
        ID3D11DeviceContext* context = gRenderAPI().GetDevice()->GetImmediateContext();

        context->IASetInputLayout(_inputLayout);

        if (HasShader(ShaderType::VERTEX_SHADER)) context->VSSetShader(_vertexShader.Shader, nullptr, 0);
        if (HasShader(ShaderType::HULL_SHADER)) context->HSSetShader(_hullShader.Shader, nullptr, 0);
        if (HasShader(ShaderType::DOMAIN_SHADER)) context->DSSetShader(_domainShader.Shader, nullptr, 0);
        if (HasShader(ShaderType::GEOMETRY_SHADER)) context->GSSetShader(_geometryShader.Shader, nullptr, 0);
        if (HasShader(ShaderType::PIXEL_SHADER)) context->PSSetShader(_pixelShader.Shader, nullptr, 0);
        if (HasShader(ShaderType::COMPUTE_SHADER)) context->CSSetShader(_computeShader.Shader, nullptr, 0);
    }

    bool Shader::HasShader(ShaderType type)
    {
        switch (type)
        {
        case ShaderType::VERTEX_SHADER:
            if (_config.VertexShaderPath.length() > 0) return true;
            break;
        case ShaderType::HULL_SHADER:
            if (_config.HullShaderPath.length() > 0) return true;
            break;
        case ShaderType::DOMAIN_SHADER:
            if (_config.DomainShaderPath.length() > 0) return true;
            break;
        case ShaderType::GEOMETRY_SHADER:
            if (_config.GeometryShaderPath.length() > 0) return true;
            break;
        case ShaderType::PIXEL_SHADER:
            if (_config.PixelShaderPath.length() > 0) return true;
            break;
        case ShaderType::COMPUTE_SHADER:
            if (_config.ComputeShaderPath.length() > 0) return true;
            break;
        default:
            return false;
            break;
        }

        return false;
    }

    HRESULT Shader::Compile()
    {
        HRESULT hr = S_OK;
        ID3D11DeviceContext* context = gRenderAPI().GetDevice()->GetImmediateContext();
        ID3D11Device* device = gRenderAPI().GetDevice()->GetD3D11Device();

        if (HasShader(ShaderType::VERTEX_SHADER))
        {
            hr = CompileVertexShader();
            hr = device->CreateVertexShader(_vertexShader.Blob->GetBufferPointer(), _vertexShader.Blob->GetBufferSize(), nullptr, &_vertexShader.Shader);
            if (FAILED(hr)) return hr;
        }

        if (HasShader(ShaderType::HULL_SHADER))
        {
            hr = CompileHullShader();
            hr = device->CreateHullShader(_hullShader.Blob->GetBufferPointer(), _hullShader.Blob->GetBufferSize(), nullptr, &_hullShader.Shader);
            if (FAILED(hr)) return hr;
        }

        if (HasShader(ShaderType::DOMAIN_SHADER))
        {
            hr = CompileDomainShader();
            hr = device->CreateDomainShader(_domainShader.Blob->GetBufferPointer(), _domainShader.Blob->GetBufferSize(), nullptr, &_domainShader.Shader);
            if (FAILED(hr)) return hr;
        }

        if (HasShader(ShaderType::GEOMETRY_SHADER)) 
        {
            hr = CompileGeometryShader();
            hr = device->CreateGeometryShader(_geometryShader.Blob->GetBufferPointer(), _geometryShader.Blob->GetBufferSize(), nullptr, &_geometryShader.Shader);
            if (FAILED(hr)) return hr;
        }

        if (HasShader(ShaderType::PIXEL_SHADER))
        {
            hr = CompilePixelShader();
            hr = device->CreatePixelShader(_pixelShader.Blob->GetBufferPointer(), _pixelShader.Blob->GetBufferSize(), nullptr, &_pixelShader.Shader);
            if (FAILED(hr)) return hr;
        }

        if (HasShader(ShaderType::COMPUTE_SHADER))
        {
            hr = CompilePixelShader();
            hr = device->CreateComputeShader(_computeShader.Blob->GetBufferPointer(), _computeShader.Blob->GetBufferSize(), nullptr, &_computeShader.Shader);
            if (FAILED(hr)) return hr;
        }

        hr = device->CreateInputLayout(
            _inputElementsDesc,
            _numberElementsDesc,
            _vertexShader.Blob->GetBufferPointer(),
            _vertexShader.Blob->GetBufferSize(),
            &_inputLayout);

        return hr;
    }

    HRESULT Shader::CompileVertexShader()
    {
        return CompileShader(_vertexShader.Path.c_str(), "VS_MAIN", "vs_5_0", &_vertexShader.Blob);
    }

    HRESULT Shader::CompileHullShader()
    {
        return CompileShader(_hullShader.Path.c_str(), "HS_MAIN", "hs_5_0", &_hullShader.Blob);
    }

    HRESULT Shader::CompileDomainShader()
    {
        return CompileShader(_vertexShader.Path.c_str(), "DS_MAIN", "ds_5_0", &_domainShader.Blob);
    }

    HRESULT Shader::CompileGeometryShader()
    {
        return CompileShader(_vertexShader.Path.c_str(), "GS_MAIN", "gs_5_0", &_geometryShader.Blob);
    }

    HRESULT Shader::CompilePixelShader()
    {
        return CompileShader(_pixelShader.Path.c_str(), "PS_MAIN", "ps_5_0", &_pixelShader.Blob);
    }

    HRESULT Shader::CompileComputeShader()
    {
        return CompileShader(_computeShader.Path.c_str(), "PS_MAIN", "ps_5_0", &_computeShader.Blob);
    }

    HRESULT Shader::CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob)
    {
        HRESULT hr = S_OK;

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(EGE_DEBUG) && defined(EGE_GRAPHIC_DEBUG)
        dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ID3DBlob* errorBlob = nullptr;
        ShaderInclude includeObj(_config.IncludeDirectory.c_str(), EGE_SHADERS_INCLUDE_FOLDER);

#if defined(EGE_WIN_SDK_8) || defined(EGE_WIN_SDK_10)
        hr = D3DCompileFromFile(srcFile, nullptr, &includeObj, entryPoint, profile, dwShaderFlags, 0, blob, &errorBlob);
#elif defined(EGE_WIN_SDK_7)
        hr = D3DX11CompileFromFile(srcFile, nullptr, &includeObj, entryPoint, profile, D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr, blob, &errorBlob, nullptr);
#endif

        if (FAILED(hr))
        {
            if (errorBlob)
            {
                OutputDebugStringA((char*)errorBlob->GetBufferPointer());
                errorBlob->Release();

                EGE_ASSERT_ERROR(SUCCEEDED(hr), ("Can't compie shader file : " + ToString(srcFile)));
            }
            else
            {
                EGE_ASSERT_ERROR(SUCCEEDED(hr), ("Can't compie shader file : " + ToString(srcFile)));
            }
        }

        return hr;
    }
}