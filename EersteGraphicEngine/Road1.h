#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Road1 : public Model
    {
    public:
        Road1();
        ~Road1();
        void Initialise() override;
        void Update();
    };
}