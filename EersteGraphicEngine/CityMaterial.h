#pragma once

#include "PrerequisitesCore.h"
#include "Material.h"

namespace ege
{
    class CityMaterial : public Material
    {
    public:
        CityMaterial(String diffuseName = "", String specularName = "");
        ~CityMaterial();
        void Initialise() override;
        void Update() override;

    private:
        String _diffuseName;
        String _specularName;
    };
}