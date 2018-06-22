#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class Frustum
    {
    public:
        Frustum();
        ~Frustum();
        void            Build(PerspectiveCamera* camera);
        bool            CheckSphere(PerspectiveCamera* camera, Model* model, const float radius = 1.0f);
        const XMVECTOR* GetPlanes() const;

    protected:
        XMVECTOR _planes[6];
    };
}