#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Road2 : public Model
    {
    public:
        Road2();
        ~Road2();
        void Initialise() override;
        void Update();
    };
}