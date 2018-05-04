#include "Model.h"

namespace ege
{
    Model::Model()
        : IEntity(EntityType::Model)
    {
    }

    Model::~Model()
    {
    }

    void Model::Initialise()
    {
    }

    void Model::Update()
    {
    }

    void Model::Draw()
    {
    }

    void Model::Build(SPtr<ModelDesc> modelDesc)
    {
    }

    void Model::SetShader(SPtr<Shader> shader)
    {
        _shader = shader;
    }

    Geometry& Model::GetGeometry()
    {
        return _geometry;
    }

    SPtr<Shader> Model::GetShader()
    {
        return _shader;
    }
}