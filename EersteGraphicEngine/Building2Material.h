#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Building2Material : public Material
    {
    public:
        Building2Material();
        ~Building2Material();
        void Initialise() override;
        void Update() override;
    };
}