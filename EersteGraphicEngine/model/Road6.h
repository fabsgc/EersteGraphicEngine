#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Road6 : public Model
    {
    public:
        Road6();
        ~Road6();
        void Initialise() override;
        void Update();
    };
}