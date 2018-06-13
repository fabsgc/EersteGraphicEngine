#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Road3Material : public Material
    {
    public:
        Road3Material();
        ~Road3Material();
        void Initialise() override;
        void Update() override;
    };
}