#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class CubeMaterial : public Material
    {
    public:
        CubeMaterial();
        ~CubeMaterial();
        void Initialise() override;
        void Update() override;
    };
}