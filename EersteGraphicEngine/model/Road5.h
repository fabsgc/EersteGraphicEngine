#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Road5 : public Model
    {
    public:
        Road5();
        ~Road5();
        void Initialise() override;
        void Update();
    };
}