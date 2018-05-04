#pragma once

#include "PrerequisitesCore.h"
#include "Light.h"

namespace ege
{
    class PointLight : public Light
    {
    public:
        PointLight();
        ~PointLight();

        void Initialise() override;
        void Update()  override;
        void Draw()  override;
    };
}