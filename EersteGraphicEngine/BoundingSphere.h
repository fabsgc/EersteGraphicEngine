#pragma once

#include "PrerequisitesCore.h"
#include "Bounding.h"

namespace ege
{
    class BoundingSphere : public Bounding
    {
    public:
        BoundingSphere(SPtr<Model> parent);
        ~BoundingSphere() {};

        virtual void Initialise() override;
        virtual void Update() override;
        virtual void CheckFrustum(const Frustum* frustum) override;

        void         SetRadius(float radius);
        const float& GetRadius() const;

    protected:
        static const float DefaultRadius;

    protected:
        float _radius;
    };
}