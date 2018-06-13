#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Building1 : public Model
    {
    public:
        Building1();
        ~Building1();
        void Initialise() override;
        void Update();
    };
}