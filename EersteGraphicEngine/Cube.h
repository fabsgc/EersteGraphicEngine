#pragma once

#include "PrerequisitesCore.h"
#include "InstancedModel.h"

namespace ege
{
    class Cube : public InstancedModel
    {
    public:
        Cube();
        ~Cube();
        void Initialise() override;
        void Update();
    };
}