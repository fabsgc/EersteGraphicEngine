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
}