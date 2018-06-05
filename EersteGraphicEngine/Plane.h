#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Plane : public Model
    {
    public:
        Plane();
        ~Plane();
        void Initialise() override;
        void Update();
    };
}