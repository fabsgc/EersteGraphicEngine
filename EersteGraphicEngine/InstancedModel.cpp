#include "InstancedModel.h"

#include "Model.h"

#include "ShaderManager.h"
#include "ModelLoader.h"
#include "VertexDesc.h"
#include "Material.h"
#include "Light.h"

#include "CoreApplication.h"

#include "PerspectiveCamera.h"

#include "RenderAPI.h"
#include "Device.h"

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
		// Create our trees instance buffer
		// Pretty much the same thing as a regular vertex buffer, except that this buffers data
		// will be used per "instance" instead of per "vertex". Each instance of the geometry
		// gets it's own instanceData data, similar to how each vertex of the geometry gets its own
		// Vertex data
		D3D11_BUFFER_DESC instBuffDesc;
		ZeroMemory(&instBuffDesc, sizeof(instBuffDesc));

		instBuffDesc.Usage = D3D11_USAGE_DEFAULT;
		instBuffDesc.ByteWidth = sizeof(XMFLOAT4X4) * EGE_MAX_INSTANCED_OBJECTS;
		instBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		instBuffDesc.CPUAccessFlags = 0;
		instBuffDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA instData;
		ZeroMemory(&instData, sizeof(instData));

		instData.pSysMem = &_worlds[0];
		HRESULT hr = _renderAPI.GetDevice()->GetD3D11Device()->CreateBuffer(&instBuffDesc, &instData, &_instanceBuffer);
	}

	void InstancedModel::Update()
	{
		Model::Update();
	}

	void InstancedModel::Draw()
	{
		UINT16 modelsToDrawCounter = 0;

		for (UINT16 i = 0; i < _instancedCounter; i++)
		{
			if (IsInFrustum(_positions[i]))
			{
				modelsToDrawCounter++;
			}
		}

		if (modelsToDrawCounter > 0)
		{
			ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
			SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::OBJECT);
			ObjectConstantBuffer* constantBufferUpdate = (ObjectConstantBuffer*)&*constantBuffer->UpdateBuffer;

			XMMATRIX world = XMLoadFloat4x4(&_worlds[0]);
			constantBufferUpdate->World = XMMatrixTranspose(world);
			constantBufferUpdate->IsInstance = true;

			for (auto i = 0; i < 100; i++)
			{
				XMMATRIX wor = XMLoadFloat4x4(&_worlds[0]);
				constantBufferUpdate->Worlds[i] = XMMatrixTranspose(wor);
			}

			if (_material != nullptr)
			{
				_material->Apply();
			}

			ID3D11Buffer* vertexBuffer = _geometry.GetVertexBuffer();
			ID3D11Buffer* indexBuffer = _geometry.GetIndexBuffer();

			Vector<WORD> indices = _geometry.GetIndices();

			UINT stride = sizeof(VertexDesc);
			UINT offset = 0;
			context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
			context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

			context->UpdateSubresource(constantBuffer->Buffer, 0, nullptr, constantBufferUpdate, 0, 0);
			context->DrawIndexedInstanced((UINT)indices.size(), _instancedCounter, 0, 0, 0);

			//_geometry.Draw();
		}
	}

	void InstancedModel::DrawMetaData()
	{
		/*UINT16 modelsToDrawCounter = 0;

		for (UINT16 i = 0; i < _instancedCounter; i++)
		{
			if (IsInFrustum(_positions[i]))
			{
				modelsToDrawCounter++;
			}
		}

		if (modelsToDrawCounter > 0)
		{
			ID3D11DeviceContext* context = _renderAPI.GetDevice()->GetImmediateContext();
			SPtr<ConstantBufferElement> constantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::OBJECT);
			ObjectConstantBuffer* constantBufferUpdate = (ObjectConstantBuffer*)&*constantBuffer->UpdateBuffer;

			XMMATRIX world = XMLoadFloat4x4(&_worlds[0]);
			constantBufferUpdate->World = XMMatrixTranspose(world);

			if (_material != nullptr)
			{
				_material->Apply(true);
			}

			_geometry.Draw();
		}*/
	}

	void InstancedModel::AddObject(SPtr<Model> model)
	{
		if (_instancedCounter < EGE_MAX_INSTANCED_OBJECTS)
		{
			_worlds[_instancedCounter] = model->GetWorld();
			_positions[_instancedCounter] = model->GetPosition();

			_instancedCounter++;
		}
		else
		{
			EGE_ASSERT_ERROR(false, "You can't add another instance for this model");
		}
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