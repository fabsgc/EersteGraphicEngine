#pragma once

#include "PrerequisitesCore.h"
#include "Light.h"

namespace ege
{
    class AmbientLight : public Light
    {
    public:
        AmbientLight();
        ~AmbientLight();

        void Initialise() override;
        void Update()  override;
        void Draw()  override;
        void DrawMetaData()  override;
    };
}