#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "Geometry.h"
#include "Model.h"
#include "Node.h"

namespace ege
{
	struct InstancedElement
	{
		XMFLOAT4X4 World;
		XMFLOAT3   Position;
	};

	class InstancedModel : public Model
	{
	public:
		InstancedModel();
		~InstancedModel();

		void Initialise() override;
		void Update() override;
		void Draw() override;
		void DrawMetaData() override;

		void AddObject(SPtr<Model> model);

	protected:
		bool IsInFrustum(XMFLOAT3 position);

	protected:
		XMFLOAT4X4         _worlds[EGE_MAX_INSTANCED_OBJECTS];
		XMFLOAT3           _positions[EGE_MAX_INSTANCED_OBJECTS];
		UINT16             _instancedCounter;

		ID3D11Buffer*      _instanceBuffer;
		ID3D11InputLayout* _leafVertLayout;
	};
}