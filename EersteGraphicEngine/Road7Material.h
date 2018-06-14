#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Road7Material : public Material
    {
    public:
        Road7Material();
        ~Road7Material();
        void Initialise() override;
        void Update() override;
    };
}