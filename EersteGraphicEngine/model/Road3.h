#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Road3 : public Model
    {
    public:
        Road3();
        ~Road3();
        void Initialise() override;
        void Update();
    };
}