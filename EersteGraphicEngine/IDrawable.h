#pragma once

namespace ege
{
    class IDrawable
    {
    public:
        IDrawable() {}
        virtual ~IDrawable() = 0 {}
        virtual void Draw() = 0;
    };
}