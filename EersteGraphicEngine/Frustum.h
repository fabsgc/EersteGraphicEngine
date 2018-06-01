#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class Frustum
    {
    public:
        Frustum();
        ~Frustum();
        void Build(const Camera& camera);
        bool CheckSphere(const Camera& camera, const float radius = 1.0f);

    private:
        XMVECTOR _planes[6];
    };
}