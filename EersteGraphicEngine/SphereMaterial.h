#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class SphereMaterial : public Material
    {
    public:
        SphereMaterial();
        ~SphereMaterial();
        void Initialise() override;
        void Update() override;
    };
}