#pragma once

#include "PrerequisitesCore.h"
#include "Bounding.h"

namespace ege
{
    class BoundingSphere : public Bounding
    {
    public:
        BoundingSphere() {};
        ~BoundingSphere() {};

        virtual void Initialise() override;
        virtual void Update() override;
        virtual void CheckFrustum(const Frustum* frustum) override;
    };
}