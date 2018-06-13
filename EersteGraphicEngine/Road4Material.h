#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Road4Material : public Material
    {
    public:
        Road4Material();
        ~Road4Material();
        void Initialise() override;
        void Update() override;
    };
}