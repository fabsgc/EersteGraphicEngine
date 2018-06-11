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

    protected:
        //TODO : remove when rotate method implemented
        static const XMFLOAT3 DefaultPosition;
        static const float    DefaultRadius;

    protected:
        float    _radius;
    };
}