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

        ConstantBufferElement* frameConstantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::FRAME);
        ConstantBufferElement* objectConstantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::OBJECT);
        ConstantBufferElement* lightConstantBuffer = _renderAPI.GetConstantBuffer(ConstantBufferType::LIGHT);

        _shader->InsertConstantBuffer(0, frameConstantBuffer);
        _shader->InsertConstantBuffer(1, objectConstantBuffer);
        _shader->InsertConstantBuffer(2, lightConstantBuffer);
    }

    void DefaultMaterial::Update()
    {
    }
}