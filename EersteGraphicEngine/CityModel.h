#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class CityModel : public Model
    {
    public:
        CityModel(String modelName, String diffuseName, String specularName);
        ~CityModel();
        void Initialise() override;
        void Update();

    private:
        String _modelName;
        String _diffuseName;
        String _specularName;
    };
}