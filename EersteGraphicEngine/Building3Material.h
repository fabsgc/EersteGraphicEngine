#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Building3Material : public Material
    {
    public:
        Building3Material();
        ~Building3Material();
        void Initialise() override;
        void Update() override;
    };
}