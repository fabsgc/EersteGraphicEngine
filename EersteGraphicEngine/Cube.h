#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Cube : public Model
    {
    public:
        Cube();
        ~Cube();
        void Initialise() override;
        void Update();
    };
}