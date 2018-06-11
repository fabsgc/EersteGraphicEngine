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

        //TODO : remove when rotate method implemented
        const XMFLOAT3& GetDirection() const;
        //TODO : remove when rotate method implemented
        void            SetDirection(XMFLOAT3 direction);

    protected:
        //TODO : remove when rotate method implemented
        static const XMFLOAT3 DefaultDirection;

    protected:
        XMFLOAT3 _direction;
    };
}