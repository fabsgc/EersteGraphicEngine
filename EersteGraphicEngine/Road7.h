#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Road7 : public Model
    {
    public:
        Road7();
        ~Road7();
        void Initialise() override;
        void Update();
    };
}