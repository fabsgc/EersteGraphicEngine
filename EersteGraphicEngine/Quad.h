#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Quad : public Model
    {
    public:
        Quad();
        ~Quad();
        void Initialise() override;
        void Update();
    };
}