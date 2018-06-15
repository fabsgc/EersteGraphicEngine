#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Building3 : public Model
    {
    public:
        Building3();
        ~Building3();
        void Initialise() override;
        void Update();
    };
}