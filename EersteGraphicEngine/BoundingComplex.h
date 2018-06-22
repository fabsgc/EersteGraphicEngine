#pragma once

#include "PrerequisitesCore.h"
#include "Bounding.h"

namespace ege
{
    class BoundingComplex : public Bounding
    {
    public:
        BoundingComplex() {};
        ~BoundingComplex() {};

        virtual void Initialise() override;
        virtual void Update() override;
        virtual void CheckFrustum(const Frustum* frustum) override;

    protected:
        Vector<SPtr<Bounding>> _boundings;
    };
}