#pragma once

#include "PrerequisitesCore.h"
#include "Light.h"

namespace ege
{
    class DirectionalLight : public Light
    {
    public:
        DirectionalLight();
        ~DirectionalLight();

        void            Initialise() override;
        void            Update()  override;
        void            Draw()  override;

        const XMFLOAT3& GetDirection() const;
        void            SetDirection(XMFLOAT3 direction);

        void            UpdateLocalPosition() override {};

    protected:
        static const XMFLOAT3 DefaultDirection;

    protected:
        XMFLOAT3 _direction;
    };
}