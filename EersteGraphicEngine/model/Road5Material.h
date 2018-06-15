#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Road5Material : public Material
    {
    public:
        Road5Material();
        ~Road5Material();
        void Initialise() override;
        void Update() override;
    };
}