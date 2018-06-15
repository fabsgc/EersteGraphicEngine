#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class GrassMaterial : public Material
    {
    public:
        GrassMaterial();
        ~GrassMaterial();
        void Initialise() override;
        void Update() override;
    };
}