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

        void Initialise() override;
        void Update()  override;
        void Draw()  override;

        virtual void     Rotate(XMVECTOR origin, XMVECTOR eulerAngles);
        virtual void     Rotate(XMVECTOR eulerAngles);
        virtual void     Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles);
        virtual void     Rotate(XMFLOAT3 eulerAngles);
        virtual void     Rotate(XMFLOAT3 origin, float yaw, float pitch, float roll);
        virtual void     Rotate(float yaw, float pitch, float roll);

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