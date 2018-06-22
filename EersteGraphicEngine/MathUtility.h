#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace ege
{
    class MathUtility
    {
    public:
        static const float G_PI;
        static const float G_PIDIV3;
        static const float G_INFINITY;

    public:
        static float    RandF();
        static float    RandF(float a, float b);
        static float    AngleFromXY(float x, float y);
        static XMVECTOR RandUnitVec3();
        static XMVECTOR RandHemisphereUnitVec3(XMVECTOR n);

        template<typename T>
        static T Min(const T& a, const T& b)
        {
            return a < b ? a : b;
        }

        template<typename T>
        static T Max(const T& a, const T& b)
        {
            return a > b ? a : b;
        }

        template<typename T>
        static T Lerp(const T& a, const T& b, float t)
        {
            return a + (b - a)*t;
        }

        template<typename T>
        static T Clamp(const T& x, const T& low, const T& high)
        {
            return x < low ? low : (x > high ? high : x);
        }
    };
}