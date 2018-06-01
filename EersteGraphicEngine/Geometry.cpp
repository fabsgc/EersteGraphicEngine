#include "Geometry.h"
#include "ModelLoader.h"

namespace ege
{
    Geometry::Geometry()
        : _renderAPI(gRenderAPI())
    {
    };

    Geometry::~Geometry()
    {
    };

    void Geometry::Build(SPtr<ModelDesc> modelDesc)
    {
        HRESULT hr;
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Device* device = _renderAPI.GetDevice()->GetD3D11Device();

        _vertices = modelDesc->Vertices;
        _indices = modelDesc->Indices;

        //############# Set vertex buffer
        D3D11_BUFFER_DESC vbd;
        ZeroMemory(&vbd, sizeof(vbd));
        vbd.Usage = D3D11_USAGE_DEFAULT;
        vbd.ByteWidth = sizeof(VertexDesc) * (UINT)_vertices.size();
        vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vbd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA vInitData;
        ZeroMemory(&vInitData, sizeof(vInitData));
        vInitData.pSysMem = &_vertices[0];
        hr = device->CreateBuffer(&vbd, &vInitData, &_vertexBuffer);
        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't initialise geometry from model description");

        //############# Set index buffer
        D3D11_BUFFER_DESC ibd;
        ZeroMemory(&ibd, sizeof(ibd));

        ibd.Usage = D3D11_USAGE_DEFAULT;
        ibd.ByteWidth = sizeof(WORD) * (UINT)_indices.size();
        ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        ibd.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA iInitData;
        ZeroMemory(&iInitData, sizeof(iInitData));
        iInitData.pSysMem = &_indices[0];
        hr = device->CreateBuffer(&ibd, &iInitData, &_indexBuffer);
        EGE_ASSERT_ERROR(SUCCEEDED(hr), "Can't initialise geometry from model description");
    }

    void Geometry::Update()
    {
    }

    void Geometry::Draw()
    {
        ID3D11DeviceContext* context = gRenderAPI().GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = gRenderAPI().GetConstantBuffer();
        ConstantBuffer* constantBufferUpdate = gRenderAPI().GetConstantBufferUpdate();

        UINT stride = sizeof(VertexDesc);
        UINT offset = 0;
        context->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
        context->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

        context->UpdateSubresource(constantBuffer, 0, nullptr, constantBufferUpdate, 0, 0);
        context->DrawIndexed((UINT)_indices.size(), 0, 0);
    }
}