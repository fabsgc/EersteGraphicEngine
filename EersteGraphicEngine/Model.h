#pragma once

#include "PrerequisitesCore.h"
#include "IMoveable.h"
#include "RenderAPI.h"
#include "Material.h"
#include "Geometry.h"
#include "IEntity.h"
#include "Shader.h"

namespace ege
{
    class Model: public IEntity, public IMoveable
    {
    public:
        Model();
        ~Model();

        void           Initialise() override;
        void           Update() override;
        void           Draw() override;
        void           Build(SPtr<ModelDesc> modelDesc);
        void           SetMaterial(SPtr<Material> shader);
        Geometry&      GetGeometry();
        SPtr<Material> GetMaterial();

        void           UpdateLocalPosition();
        
    private:
        RenderAPI&     _renderAPI;

        SPtr<Material> _material;
        Geometry       _geometry;
    };
}