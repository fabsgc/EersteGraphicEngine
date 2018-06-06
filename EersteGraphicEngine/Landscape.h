#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Landscape : public Model
    {
    public:
        Landscape();
        ~Landscape();
        void Initialise() override;
        void Update();
    };
}