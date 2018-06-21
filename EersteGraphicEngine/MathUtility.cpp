#include "MathUtility.h"
#include <cmath>

namespace ege
{
    const float MathUtility::G_PI = 3.14159f;
    const float MathUtility::G_PIDIV3 = 1.0471975512f;
    const float MathUtility::G_INFINITY = FLT_MAX;

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
}