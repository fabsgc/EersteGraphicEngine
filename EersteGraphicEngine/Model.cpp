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
        if (_material != nullptr)
        {
            _material->Update();
        }
    }

    void Model::Draw()
    {
        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ID3D11Buffer* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::OBJECT);
        ObjectConstantBuffer* constantBufferUpdate = (ObjectConstantBuffer*)gRenderAPI().GetConstantBufferUpdate(ConstantBufferType::OBJECT);

        XMMATRIX world = XMLoadFloat4x4(&_world);
        constantBufferUpdate->World = XMMatrixTranspose(world);

        if (_material != nullptr)
        {
            _material->Apply();
        }
        
        _geometry.Draw();
    }

    void Model::Build(SPtr<ModelDesc> modelDesc)
    {
        _geometry.Build(modelDesc);
    }

    void Model::SetMaterial(SPtr<Material> material)
    {
        _material = material;
    }

    Geometry& Model::GetGeometry()
    {
        return _geometry;
    }

    SPtr<Material> Model::GetMaterial()
    {
        return _material;
    }

    void Model::UpdateLocalPosition()
    {
        XMMATRIX worldInverse = XMMatrixInverse(nullptr, XMLoadFloat4x4(&_world));
        XMVECTOR position = XMVector3Transform(XMLoadFloat3(&_position), XMLoadFloat4x4(&_world));
        XMStoreFloat3(&_position, position);
    }
}