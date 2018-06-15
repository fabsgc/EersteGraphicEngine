#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Road4 : public Model
    {
    public:
        Road4();
        ~Road4();
        void Initialise() override;
        void Update();
    };
}