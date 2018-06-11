#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class LightSchema : public Model
    {
    public:
        LightSchema(String name);
        ~LightSchema();
        void Initialise() override;

    protected:
        String _name;
    };
}