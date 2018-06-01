#include "Material.h"

namespace ege
{
    Material::Material()
        : _renderAPI(gRenderAPI())
        , _shader(nullptr)
    {}

    Material::Material(SPtr<Shader> shader)
        : _renderAPI(gRenderAPI())
        ,_shader(shader) 
    {}

    void Material::Initialise()
    {
    }

    void Material::Update()
    {
    }

    void Material::Apply()
    {
        if (_shader != nullptr)
        {
            _shader->Apply();
        }
        
        for (auto texture : _textures)
        {
            texture.second->Apply(texture.first);
        }
    }
}