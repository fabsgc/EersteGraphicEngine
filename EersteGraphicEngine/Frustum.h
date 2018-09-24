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
		const bool      CheckSphere(PerspectiveCamera* camera, Model* model, const float radius = 1.0f) const;
		const bool      CheckSphere(PerspectiveCamera* camera, const XMFLOAT3& position, const float radius = 1.0f) const;
        const XMVECTOR* GetPlanes() const;

    protected:
        XMVECTOR _planes[6];
    };
}