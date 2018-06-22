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

        virtual void    Rotate(XMVECTOR origin, XMVECTOR eulerAngles);
        virtual void    Rotate(XMVECTOR eulerAngles);
        virtual void    Rotate(XMFLOAT3 origin, XMFLOAT3 eulerAngles);
        virtual void    Rotate(XMFLOAT3 eulerAngles);
        virtual void    Rotate(XMFLOAT3 origin, float yaw, float pitch, float roll);
        virtual void    Rotate(float yaw, float pitch, float roll);

        const XMFLOAT3& GetDirection() const;
        void            SetDirection(XMFLOAT3 direction);

    protected:
        static const XMFLOAT3 DefaultPosition;
        static const XMFLOAT3 DefaultDirection;

    protected:
        XMFLOAT3 _direction;
    };
}