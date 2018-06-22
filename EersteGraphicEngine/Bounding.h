#pragma once

#include "PrerequisitesCore.h"
#include "IUpdatable.h"

namespace ege
{
    class Bounding : IUpdatable
    {
    public:
        Bounding(SPtr<Model> parent);
        ~Bounding() {};

        virtual void Initialise() {};
        virtual void Update() {};
        virtual void CheckFrustum(const Frustum* frustum) = 0;

        void         SetParent(SPtr<Model> parent);
        SPtr<Model>  GetParentPtr();
        void         SetRelativePosition(XMFLOAT3 relativePosition);
        XMFLOAT3     GetRelativePosition();

    protected:
        static const XMFLOAT3 DefaultRelativePosition;

    protected:
        SPtr<Model> _parent;
        XMFLOAT3    _relativePosition;
    };
}