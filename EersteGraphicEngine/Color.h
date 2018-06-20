#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class Color
    {
    public:
        Color();
        Color(const float& r, const float& g, const float& b, const float& a = DefaultColorA);
        Color(const XMFLOAT3& Color);
        Color(const XMFLOAT4& Color);

        XMFLOAT3 ToXMFLOAT3() const;
        XMFLOAT4 ToXMFLOAT4() const;

        const float& R() const;
        const float& G() const;
        const float& B() const;
        const float& A() const;

    private:
        static const float DefaultColorR;
        static const float DefaultColorG;
        static const float DefaultColorB;
        static const float DefaultColorA;

    private:
        float _r;
        float _g;
        float _b;
        float _a;
    };
}