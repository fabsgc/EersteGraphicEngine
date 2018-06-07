#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class DefaultMaterial : public Material
    {
    public:
        DefaultMaterial();
        ~DefaultMaterial();
        void Initialise() override;
        void Update() override;
    };
}