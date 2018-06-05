#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Sphere : public Model
    {
    public:
        Sphere();
        ~Sphere();
        void Initialise() override;
        void Update();
    };
}