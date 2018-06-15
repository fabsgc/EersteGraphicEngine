#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Road6Material : public Material
    {
    public:
        Road6Material();
        ~Road6Material();
        void Initialise() override;
        void Update() override;
    };
}