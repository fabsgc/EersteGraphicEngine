#pragma once

#include "Bounding.h"

namespace ege
{
    const XMFLOAT3 Bounding::DefaultRelativePosition = XMFLOAT3(0.0f, 0.0f, 0.0f);

    Bounding::Bounding(SPtr<Model> parent)
        : _parent(parent)
        , _relativePosition(DefaultRelativePosition)
    {}

    void Bounding::SetParent(SPtr<Model> parent)
    {
        _parent = parent;
    }

    SPtr<Model> Bounding::GetParentPtr()
    {
        return _parent;
    }

    void Bounding::SetRelativePosition(XMFLOAT3 relativePosition)
    {
        _relativePosition = relativePosition;
    }
    XMFLOAT3 Bounding::GetRelativePosition()
    {
        return _relativePosition;
    }
}