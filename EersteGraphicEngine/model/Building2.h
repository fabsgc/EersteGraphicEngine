#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Building2 : public Model
    {
    public:
        Building2();
        ~Building2();
        void Initialise() override;
        void Update();
    };
}