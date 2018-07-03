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
        void            Update() override;
        void            Draw() override;
        void            DrawMetaData() override;

        using           Light::Rotate;
        virtual void    Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override;
        virtual void    Rotate(XMVECTOR eulerAngles) override;

        const XMFLOAT3& GetDirection() const;
        void            SetDirection(XMFLOAT3 direction);

    protected:
        static const XMFLOAT3 DefaultPosition;
        static const XMFLOAT3 DefaultDirection;

    protected:
        XMFLOAT3 _direction;
    };
}