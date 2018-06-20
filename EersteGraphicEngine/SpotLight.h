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

        //TODO : remove when rotate method implemented
        const XMFLOAT3& GetDirection() const;
        //TODO : remove when rotate method implemented
        void            SetDirection(XMFLOAT3 direction);

        void            SetRadius(float radius);
        const float&    GetRadius() const;

    protected:
        //TODO : remove when rotate method implemented
        static const XMFLOAT3 DefaultDirection;
        //TODO : remove when rotate method implemented
        static const XMFLOAT3 DefaultPosition;
        static const float    DefaultRadius;

    protected:
        XMFLOAT3 _direction;
        float    _radius;
    };
}