#pragma once

#include "PrerequisitesCore.h"
#include "InstancedModel.h"

namespace ege
{
    class Plane : public InstancedModel
    {
    public:
        Plane();
        ~Plane();
        void Initialise() override;
        void Update();
    };
}