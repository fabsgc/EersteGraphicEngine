#include "Model.h"

#include "ShaderManager.h"
#include "ModelLoader.h"
#include "VertexDesc.h"

namespace ege
{
    Model::Model()
        : IEntity(EntityType::Model)
        , _renderAPI(gRenderAPI())
    {
        XMStoreFloat4x4(&_world, XMMatrixIdentity());
    }

    Model::~Model()
    {
    }

    void Model::Initialise()
    {
    }

    void Model::Update()
    {
    }

    void Model::Draw()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer();
        ConstantBuffer* constantBufferUpdate = _renderAPI.GetConstantBufferUpdate();

        XMMATRIX world = XMLoadFloat4x4(&_world);
        constantBufferUpdate->World = XMMatrixTranspose(world);

        _shader->Apply();
        _geometry.Draw();
    }

    void Model::Build(SPtr<ModelDesc> modelDesc)
    {
        _geometry.Build(modelDesc);
    }

    void Model::SetShader(SPtr<Shader> shader)
    {
        _shader = shader;
    }

    Geometry& Model::GetGeometry()
    {
        return _geometry;
    }

    SPtr<Shader> Model::GetShader()
    {
        return _shader;
    }
}