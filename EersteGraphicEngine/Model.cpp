#include "Model.h"

#include "ShaderManager.h"
#include "ModelLoader.h"
#include "VertexDesc.h"
#include "Material.h"
#include "Light.h"

namespace ege
{
    const bool Model::DefaultCastShadow     = true;
    const LightMode Model::DefaultLightMode = LightMode::All;

    Model::Model()
        : Node(NodeType::Model)
        , _renderAPI(gRenderAPI())
        , _castShadow(DefaultCastShadow)
        , _lightMode(DefaultLightMode)
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
        Node::Update();

        if (_material != nullptr)
        {
            _material->Update();
        }
    }

    void Model::Draw()
    {
        Node::Draw();

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        ConstantBufferElement* constantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::OBJECT);
        ObjectConstantBuffer* constantBufferUpdate = (ObjectConstantBuffer*)&*constantBuffer->UpdateBuffer;

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
        _modelDesc = modelDesc;
        _geometry.Build(modelDesc);
    }

    void Model::SetColor(const Color color)
    {
        _geometry.SetColor(color);
        _geometry.Build(nullptr);
    }

    void Model::SetMaterial(SPtr<Material> material)
    {
        _material = material;
    }

    void Model::SetCastShadow(bool castShadow)
    {
        _castShadow = castShadow;
    }

    void Model::SetLightMode(LightMode lightMode)
    {
        lightMode = _lightMode;
    }

    void Model::AddLights(SPtr<Light> light)
    {
        _lights.push_back(light);
    }

    Geometry& Model::GetGeometry()
    {
        return _geometry;
    }

    SPtr<Material> Model::GetMaterial()
    {
        return _material;
    }

    bool Model::GetCastShadow() const
    {
        return _castShadow;
    }

    const LightMode& Model::GetLightMode() const
    {
        return _lightMode;
    }

    Vector<SPtr<Light>>& Model::GetLights()
    {
        return _lights;
    }
}