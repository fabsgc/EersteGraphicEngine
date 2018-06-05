#pragma once

#include "PrerequisitesCore.h"
#include "DirectionalLight.h"

namespace ege
{
    class PointLight : public DirectionalLight
    {
    public:
        PointLight();
        ~PointLight();

        void Initialise() override;
        void Update()  override;
        void Draw()  override;

    protected:
        static const XMFLOAT3 DefaultPosition;
        static const float    DefaultRadius;

    protected:
        float    _radius;
    };
}