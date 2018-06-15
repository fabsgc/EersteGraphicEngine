#pragma once
#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class Shop1Material : public Material
    {
    public:
        Shop1Material();
        ~Shop1Material();
        void Initialise() override;
        void Update() override;
    };
}