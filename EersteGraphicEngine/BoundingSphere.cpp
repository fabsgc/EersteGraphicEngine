#include "BoundingSphere.h"

namespace ege
{
    const float BoundingSphere::DefaultRadius = 1.0f;

    BoundingSphere::BoundingSphere(SPtr<Model> parent)
        : Bounding(parent)
        , _radius(DefaultRadius)
    {}

    void BoundingSphere::Initialise()
    {
    }

    void BoundingSphere::Update()
    {
    }

    void BoundingSphere::CheckFrustum(const Frustum* frustum)
    {
    }

    void BoundingSphere::SetRadius(float radius)
    {
        _radius = radius;
    }

    const float& BoundingSphere::GetRadius() const
    {
        return _radius;
    }
}