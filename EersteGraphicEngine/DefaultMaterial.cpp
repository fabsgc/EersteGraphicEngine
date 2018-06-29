#include "DefaultMaterial.h"
#include "ShaderManager.h"

namespace ege
{
    DefaultMaterial::DefaultMaterial()
        : Material()
    {
    }

    DefaultMaterial::~DefaultMaterial()
    {
    }

    void DefaultMaterial::Initialise()
    {
        _shader = gShaderManager().GetPtr("forward-default");
        _shaderMetaData = gShaderManager().GetPtr("forward-meta-data");

        SPtr<ConstantBufferElement> frameConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::FRAME);
        SPtr<ConstantBufferElement> objectConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::OBJECT);
        SPtr<ConstantBufferElement> lightConstantBuffer = _renderAPI.GetConstantBufferPtr(ConstantBufferType::LIGHT);

        _shader->InsertConstantBuffer(0, frameConstantBuffer);
        _shader->InsertConstantBuffer(1, objectConstantBuffer);
        _shader->InsertConstantBuffer(2, lightConstantBuffer);
    }

    void DefaultMaterial::Update()
    {
    }
}