#include "BoundingBox.h"

namespace ege
{
    BoundingBox::BoundingBox(SPtr<Model> parent)
        : Bounding(parent)
    {}

    void BoundingBox::Initialise()
    {
    }

    void BoundingBox::Update()
    {
    }

    void BoundingBox::CheckFrustum(const Frustum* frustum)
    {
    }
}