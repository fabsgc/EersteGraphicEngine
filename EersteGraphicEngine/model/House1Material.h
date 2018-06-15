#pragma once
#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class House1Material : public Material
    {
    public:
        House1Material();
        ~House1Material();
        void Initialise() override;
        void Update() override;
    };
}