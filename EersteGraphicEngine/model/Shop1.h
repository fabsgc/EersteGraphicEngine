#pragma once

#include "PrerequisitesCore.h"
#include "Model.h"

namespace ege
{
    class Shop1 : public Model
    {
    public:
        Shop1();
        ~Shop1();
        void Initialise() override;
        void Update();
    };
}