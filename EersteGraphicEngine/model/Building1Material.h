#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Building1Material : public Material
    {
    public:
        Building1Material();
        ~Building1Material();
        void Initialise() override;
        void Update() override;
    };
}