#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class PlaneMaterial : public Material
    {
    public:
        PlaneMaterial();
        ~PlaneMaterial();
        void Initialise() override;
        void Update() override;
    };
}