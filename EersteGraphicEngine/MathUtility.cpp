#include "MathUtility.h"

namespace ege
{
    const float MathUtility::G_PI = 3.14159f;
    const float MathUtility::G_PIDIV3 = 1.0471975512f;

    float MathUtility::Clamp(float x, float a, float b)
    {
        return x < a ? a : (x > b ? b : x);
    }
}