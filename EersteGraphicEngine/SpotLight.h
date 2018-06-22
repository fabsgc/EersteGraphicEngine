#pragma once

#include "PrerequisitesCore.h"
#include "Light.h"

namespace ege
{
    class SpotLight : public Light
    {
    public:
        SpotLight();
        ~SpotLight();

        void            Initialise() override;
        void            Update()  override;
        void            Draw()  override;

        using           Light::Rotate;
        virtual void    Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override;
        virtual void    Rotate(XMVECTOR eulerAngles) override;

        const XMFLOAT3& GetDirection() const;
        void            SetDirection(XMFLOAT3 direction);

        void            SetRadius(float radius);
        const float&    GetRadius() const;
        void            SetInnerAngle(float innerAngle);
        const float&    GetInnerAngle() const;
        void            SetOuterAngle(float outerAngle);
        const float&    GetOuterAngle() const;

    protected:
        static const XMFLOAT3 DefaultDirection;
        static const XMFLOAT3 DefaultPosition;

        static const float    DefaultRadius;
        static const float    DefaultInnerAngle;
        static const float    DefaultOuterAngle;

    protected:
        XMFLOAT3 _direction;
        float    _radius;
        float    _innerAngle;
        float    _outerAngle;
    };
}