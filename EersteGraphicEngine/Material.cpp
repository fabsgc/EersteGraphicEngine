#include "Material.h"

namespace ege
{
    Material::Material(SPtr<Shader> shader)
        : _renderAPI(gRenderAPI())
        ,_shader(shader) 
    {
    }

    void Material::Apply()
    {
        _shader->Apply();
    }
}