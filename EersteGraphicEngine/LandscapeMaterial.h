#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class LandscapeMaterial : public Material
    {
    public:
        LandscapeMaterial();
        ~LandscapeMaterial();
        void Initialise() override;
        void Update() override;
    };
}