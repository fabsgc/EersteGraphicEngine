#pragma once

#include "PrerequisitesCore.h"
#include "Bounding.h"

namespace ege
{
    class BoundingBox : public Bounding
    {
    public:
        BoundingBox(SPtr<Model> parent);
        ~BoundingBox() {};

        virtual void Initialise() override;
        virtual void Update() override;
        virtual void CheckFrustum(const Frustum* frustum) override;
    };
}