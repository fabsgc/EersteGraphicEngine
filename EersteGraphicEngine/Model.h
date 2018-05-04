#pragma once

#include "PrerequisitesCore.h"
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

        void Initialise() override;
        void Update() override;
        void Draw() override;
        
    private:
        SPtr<Shader> _shader;
        Geometry     _geometry;
    };
}