#include "PlaneMaterial.h"
#include "ShaderManager.h"

#include "TextureManager.h"

namespace ege
{
	PlaneMaterial::PlaneMaterial()
		: Material()
	{
	}

	PlaneMaterial::~PlaneMaterial()
	{
	}

	void PlaneMaterial::Initialise()
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
		_hasDiffuseTexture = true;
		_hasSpecularTexture = true;
		_hasNormalTexture = false;

		_specularPower = 16.0f;

		InsertTexture(0, gTextureManager().GetPtr("grass-diffuse"));
		InsertTexture(1, gTextureManager().GetPtr("grass-specular"));
	}

	void PlaneMaterial::Update()
	{
	}
}