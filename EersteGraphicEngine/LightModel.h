#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Model;

    class LightModel : public Model
    {
    public:
        LightModel(String name);
        ~LightModel();
        void Initialise() override;

    protected:
        String _name;
    };
}