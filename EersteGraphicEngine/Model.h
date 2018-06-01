#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"
#include "Geometry.h"
#include "IEntity.h"
#include "Shader.h"

namespace ege
{
    class Model: public IEntity
    {
    public:
        Model();
        ~Model();

        void         Initialise() override;
        void         Update() override;
        void         Draw() override;
        void         Build(SPtr<ModelDesc> modelDesc);
        void         SetShader(SPtr<Shader> shader);
        Geometry&    GetGeometry();
        SPtr<Shader> GetShader();
        
    private:
        RenderAPI&   _renderAPI;

        SPtr<Shader> _shader;
        Geometry     _geometry;
    };
}