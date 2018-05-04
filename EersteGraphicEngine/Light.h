#pragma once

#include "PrerequisitesCore.h"
#include "IEntity.h"
#include "Shader.h"

namespace ege
{
    class Light: public IEntity
    {
    public:
        Light();
        ~Light();

        void Initialise() override;
        void Update() override;
        void Draw() override;

    private:
        SPtr<Shader> _shader;
    };
}