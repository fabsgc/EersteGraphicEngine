#include "Model.h"

#include "ShaderManager.h"
#include "ModelLoader.h"
#include "VertexDesc.h"
#include "Material.h"
#include "Light.h"

#include "CoreApplication.h"

#include "PerspectiveCamera.h"

namespace ege
{
	const bool Model::DefaultCastShadow = true;
    const LightMode Model::DefaultLightMode = LightMode::All;

	Model::Model()
		: Node(NodeType::Model)
		, _renderAPI(gRenderAPI())
		, _application(gCoreApplication())
		, _scene(*_application.GetScene())
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
        //Node::Draw();

		if (IsInFrustum() == false)
		{
			return;
		}

        ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
        SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::OBJECT);
        ObjectConstantBuffer* constantBufferUpdate = (ObjectConstantBuffer*)&*constantBuffer->UpdateBuffer;

        XMMATRIX world = XMLoadFloat4x4(&_world);
        constantBufferUpdate->World = XMMatrixTranspose(world);
		constantBufferUpdate->IsInstance = false;

        if (_material != nullptr)
        {
            _material->Apply();
        }
        
        _geometry.Draw();
    }

    void Model::DrawMetaData()
    {
        //Node::DrawMetaData();

		if (IsInFrustum() == false)
		{
			return;
		}

		ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
		SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::OBJECT);
		ObjectConstantBuffer* constantBufferUpdate = (ObjectConstantBuffer*)&*constantBuffer->UpdateBuffer;

		XMMATRIX world = XMLoadFloat4x4(&_world);
		constantBufferUpdate->World = XMMatrixTranspose(world);

		if (_material != nullptr)
		{
			_material->Apply(true);
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

	SPtr<ModelDesc> Model::GetModelDesc()
	{
		return _modelDesc;
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

	bool Model::IsInFrustum()
	{
		SPtr<Camera> camera = _scene.GetActiveCamera();
		CameraType cameraType = camera->GetType();

		if (cameraType == CameraType::FirstPersonCamera || cameraType == CameraType::ThirdPersonCamera || cameraType == CameraType::FlyingCamera)
		{
			PerspectiveCamera& perspectiveCamera = static_cast<PerspectiveCamera&>(*camera);

			if (!perspectiveCamera.GetFrustum().CheckSphere(&perspectiveCamera, this, 2.0f))
			{
				return false;
			}
		}

		return true;
	}
}