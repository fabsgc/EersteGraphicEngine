#include "CubeMaterial.h"
#include "ShaderManager.h"

namespace ege
{
	CubeMaterial::CubeMaterial()
		: Material()
	{
	}

	CubeMaterial::~CubeMaterial()
	{
	}

	void CubeMaterial::Initialise()
	{
		_shader = gShaderManager().GetPtr("forward-default");
		_shaderMetaData = gShaderManager().GetPtr("forward-meta-data");

		SPtr<ConstantBufferElement> frameConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::FRAME);
		SPtr<ConstantBufferElement> objectConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::OBJECT);
		SPtr<ConstantBufferElement> lightConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);

		_shader->InsertConstantBuffer(0, frameConstantBuffer);
		_shader->InsertConstantBuffer(1, objectConstantBuffer);
		_shader->InsertConstantBuffer(2, lightConstantBuffer);

		_shaderMetaData->InsertConstantBuffer(0, frameConstantBuffer);
		_shaderMetaData->InsertConstantBuffer(1, objectConstantBuffer);
		_shaderMetaData->InsertConstantBuffer(2, lightConstantBuffer);

		_hasSpecular = true;
		_hasEmit = false;
		_hasDiffuseTexture = false;
		_hasSpecularTexture = false;
		_hasNormalTexture = false;

		_specularPower = 16.0f;
	}

	void CubeMaterial::Update()
	{
	}
}