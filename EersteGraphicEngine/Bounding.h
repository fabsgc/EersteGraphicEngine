#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"

namespace ege
{
    class Bounding : IUpdatable
    {
    public:
        Bounding() {};
        virtual ~Bounding() = 0;

        virtual void Initialise() {};
        virtual void Update() {};
        virtual void CheckFrustum(const Frustum* frustum) = 0;
    };
}