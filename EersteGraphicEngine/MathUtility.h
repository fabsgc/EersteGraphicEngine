#pragma once

namespace ege
{
    class MathUtility
    {
    public:
        static const float G_PI;
        static const float G_PIDIV3;

    public:
        static float Clamp(float x, float a, float b);
    };
}