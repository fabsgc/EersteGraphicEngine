#include "MathUtility.h"
#include <cmath>

namespace ege
{
    const float MathUtility::G_PI        = 3.14159f;
    const float MathUtility::G_PIDIV2    = 1.57079633f;
    const float MathUtility::G_PIDIV3    = 1.0471975512f;
    const float MathUtility::G_PIDIV4    = 0.785398163f;
    const float MathUtility::G_PIDIV6    = 0.523598776f;
    const float MathUtility::G_INFINITY  = FLT_MAX;

    const XMFLOAT3 MathUtility::Zero     = XMFLOAT3(0.0f, 0.0f, 0.0f);
    const XMFLOAT3 MathUtility::One      = XMFLOAT3(1.0f, 1.0f, 1.0f);
    const XMFLOAT3 MathUtility::Forward  = XMFLOAT3(0.0f, 0.0f, -1.0f);
    const XMFLOAT3 MathUtility::Backward = XMFLOAT3(0.0f, 0.0f, 1.0f);
    const XMFLOAT3 MathUtility::Up       = XMFLOAT3(0.0f, 1.0f, 0.0f);
    const XMFLOAT3 MathUtility::Down     = XMFLOAT3(0.0f, -1.0f, 0.0f);
    const XMFLOAT3 MathUtility::Right    = XMFLOAT3(1.0f, 0.0f, 0.0f);
    const XMFLOAT3 MathUtility::Left     = XMFLOAT3(-1.0f, 0.0f, 0.0f);

    float MathUtility::RandF()
    {
        return (float)(rand()) / (float)RAND_MAX;
    }

    float MathUtility::RandF(float a, float b)
    {
        return a + RandF()*(b - a);
    }

    float MathUtility::AngleFromXY(float x, float y)
    {
        float theta = 0.0f;

        // Quadrant I or IV
        if (x >= 0.0f)
        {
            // If x = 0, then atanf(y/x) = +pi/2 if y > 0
            //                atanf(y/x) = -pi/2 if y < 0
            theta = atanf(y / x); // in [-pi/2, +pi/2]

            if (theta < 0.0f)
                theta += 2.0f * G_PI; // in [0, 2*pi).
        }

        // Quadrant II or III
        else
        {
            theta = atanf(y / x) + G_PI; // in [0, 2*pi).
        }
            

        return theta;
    }

    XMVECTOR MathUtility::RandUnitVec3()
    {
        XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
        XMVECTOR Zero = XMVectorZero();

        // Keep trying until we get a point on/in the hemisphere.
        while (true)
        {
            // Generate random point in the cube [-1,1]^3.
            XMVECTOR v = XMVectorSet(RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), 0.0f);

            // Ignore points outside the unit sphere in order to get an even distribution 
            // over the unit sphere.  Otherwise points will clump more on the sphere near 
            // the corners of the cube.

            if (XMVector3Greater(XMVector3LengthSq(v), One))
                continue;

            return XMVector3Normalize(v);
        }
    }

    XMVECTOR MathUtility::RandHemisphereUnitVec3(XMVECTOR n)
    {
        XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
        XMVECTOR Zero = XMVectorZero();

        // Keep trying until we get a point on/in the hemisphere.
        while (true)
        {
            // Generate random point in the cube [-1,1]^3.
            XMVECTOR v = XMVectorSet(RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), 0.0f);

            // Ignore points outside the unit sphere in order to get an even distribution 
            // over the unit sphere.  Otherwise points will clump more on the sphere near 
            // the corners of the cube.

            if (XMVector3Greater(XMVector3LengthSq(v), One))
                continue;

            // Ignore points in the bottom hemisphere.
            if (XMVector3Less(XMVector3Dot(n, v), Zero))
                continue;

            return XMVector3Normalize(v);
        }
    }

    float MathUtility::cosInterpolate(float a, float b, float blend)
    {
        float ft = blend * G_PI;
        float f = (1.0f - cos(ft)) * 0.5f;

        return a * (1.0f - f) + b * f;
    }

    XMFLOAT2 MathUtility::Normalize(XMFLOAT2& vector)
    {
        XMVECTOR V = XMLoadFloat2(&vector);
        V = XMVector2Normalize(V);
        XMStoreFloat2(&vector, V);

        return vector;
    }

    XMFLOAT3 MathUtility::Normalize(XMFLOAT3& vector)
    {
        XMVECTOR V = XMLoadFloat3(&vector);
        V = XMVector3Normalize(V);
        XMStoreFloat3(&vector, V);

        return vector;
    }

    XMFLOAT4 MathUtility::Normalize(XMFLOAT4& vector)
    {
        XMVECTOR V = XMLoadFloat4(&vector);
        V = XMVector4Normalize(V);
        XMStoreFloat4(&vector, V);

        return vector;
    }

    float MathUtility::RadiansToDegrees(float radians)
    {
        return (radians * 180.0f) / G_PI;
    }

    float MathUtility::DegreesToRadians(float degrees)
    {
        return (degrees * G_PI) / 180.0f;
    }

    XMFLOAT3 MathUtility::ConvertToScreenSpace(XMFLOAT3& position, XMFLOAT4& view, XMFLOAT4& projection)
    {
        return MathUtility::One;
    }

    XMFLOAT3 MathUtility::ClipSpaceToScreenSpace(XMFLOAT4& coords)
    {
        return MathUtility::One;
    }

    float MathUtility::FloatPrecision(float value, float precision)
    {
        return ((float) floor((value * (float) pow(10, precision) + 0.5)) / (float) pow(10, precision));
    }
}