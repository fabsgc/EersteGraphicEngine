#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "Geometry.h"
#include "Model.h"
#include "Node.h"

namespace ege
{
	class InstancedModel : public Model
	{
	public:
		InstancedModel();
		~InstancedModel();

		void          Initialise() override;
		void          Update() override;
		void          Draw() override;
		void          DrawMetaData() override;

	protected:
		XMFLOAT4X4         _worlds[169];
		ID3D11Buffer*      _instanceBuffer;
		ID3D11InputLayout* _leafVertLayout;
	};
}