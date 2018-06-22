#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class Frustum
    {
    public:
        Frustum();
        ~Frustum();
        void Build(PerspectiveCamera* camera);
        bool CheckSphere(PerspectiveCamera* camera, const float radius = 1.0f);

    protected:
        XMVECTOR _planes[6];
    };
}