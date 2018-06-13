#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Grass : public Model
    {
    public:
        Grass();
        ~Grass();
        void Initialise() override;
        void Update();
    };
}