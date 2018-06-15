#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Road1Material : public Material
    {
    public:
        Road1Material();
        ~Road1Material();
        void Initialise() override;
        void Update() override;
    };
}