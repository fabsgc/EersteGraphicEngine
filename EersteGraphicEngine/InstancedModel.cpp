#include "InstancedModel.h"

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
	InstancedModel::InstancedModel()
		: Model()
		, _instancedCounter(0)
	{
		XMStoreFloat4x4(&_world, XMMatrixIdentity());
	}

	InstancedModel::~InstancedModel()
	{
	}

	void InstancedModel::Initialise()
	{
	}

	void InstancedModel::Update()
	{
		Model::Update();

		if (_material != nullptr)
		{
			_material->Update();
		}
	}

	void InstancedModel::Draw()
	{
		//Node::Draw();
	}

	void InstancedModel::DrawMetaData()
	{
		//Node::DrawMetaData();
	}

	void InstancedModel::AddObject(SPtr<Model> model)
	{
		_worlds[_instancedCounter]   = model->GetWorld();
		_position[_instancedCounter] = model->GetPosition();

		_instancedCounter++;
	}

	bool InstancedModel::IsInFrustum(XMFLOAT3 position)
	{
		SPtr<Camera> camera = _scene.GetActiveCamera();
		CameraType cameraType = camera->GetType();

		if (cameraType == CameraType::FirstPersonCamera || cameraType == CameraType::ThirdPersonCamera || cameraType == CameraType::FlyingCamera)
		{
			PerspectiveCamera& perspectiveCamera = static_cast<PerspectiveCamera&>(*camera);

			if (!perspectiveCamera.GetFrustum().CheckSphere(&perspectiveCamera, position, 2.0f))
			{
				return false;
			}
		}

		return true;
	}
}