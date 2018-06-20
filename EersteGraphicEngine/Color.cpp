#include "Color.h"

namespace ege
{
    const float Color::DefaultColorR = 255.0f;
    const float Color::DefaultColorG = 255.0f;
    const float Color::DefaultColorB = 255.0f;
    const float Color::DefaultColorA = 1.0f;

    Color::Color()
        : _r(DefaultColorR)
        , _g(DefaultColorG)
        , _b(DefaultColorB)
        , _a(DefaultColorA)
    {}

    Color::Color(const float& r, const float& g, const float& b, const float& a)
        : _r(r)
        , _g(g)
        , _b(b)
        , _a(a)
    {}

    Color::Color(const XMFLOAT3& color)
        : _r(color.x * 255.0f)
        , _g(color.y * 255.0f)
        , _b(color.z * 255.0f)
        , _a(Color::DefaultColorA)
    {
    }

    Color::Color(const XMFLOAT4& color)
        : _r(color.x * 255.0f)
        , _g(color.y * 255.0f)
        , _b(color.z * 255.0f)
        , _a(color.w)
    {
    }

    XMFLOAT3 Color::ToXMFLOAT3() const
    {
        return XMFLOAT3(_r / 255.0f, _g / 255.0f, _b / 255.0f);
    }

    XMFLOAT4 Color::ToXMFLOAT4() const
    {
        return XMFLOAT4(_r / 255.0f, _g / 255.0f, _b / 255.0f, _a);
    }
}