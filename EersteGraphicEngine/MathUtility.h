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

        static const XMFLOAT3 Zero;
        static const XMFLOAT3 One;
        static const XMFLOAT3 Forward;
        static const XMFLOAT3 Backward;
        static const XMFLOAT3 Up;
        static const XMFLOAT3 Down;
        static const XMFLOAT3 Right;
        static const XMFLOAT3 Left;

    public:
        static float    RandF();
        static float    RandF(float a, float b);
        static float    AngleFromXY(float x, float y);
        static XMVECTOR RandUnitVec3();
        static XMVECTOR RandHemisphereUnitVec3(XMVECTOR n);

        static float    cosInterpolate(float a, float b, float blend);

        static XMFLOAT2 Normalize(XMFLOAT2& vector);
        static XMFLOAT3 Normalize(XMFLOAT3& vector);
        static XMFLOAT4 Normalize(XMFLOAT4& vector);

        static float    RadiansToDegrees(float radians);
        static float    DegreesToRadians(float degrees);

        static XMFLOAT3 ConvertToScreenSpace(XMFLOAT3& position, XMFLOAT4& view, XMFLOAT4& projection);
        static XMFLOAT3 ClipSpaceToScreenSpace(XMFLOAT4& coords);

        static float FloatPrecision(float value, float precision);

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

    private:
        MathUtility();
        MathUtility(const MathUtility& rhs) = delete;
        MathUtility& operator=(const MathUtility& rhs) = delete;
    };
}