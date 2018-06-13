#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Road2Material : public Material
    {
    public:
        Road2Material();
        ~Road2Material();
        void Initialise() override;
        void Update() override;
    };
}