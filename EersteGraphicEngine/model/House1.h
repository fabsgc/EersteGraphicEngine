#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class House1 : public Model
    {
    public:
        House1();
        ~House1();
        void Initialise() override;
        void Update();
    };
}