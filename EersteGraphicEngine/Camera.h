#pragma once

#include "PrerequisitesCore.h"
#include "IEntity.h"

namespace ege
{
    class Camera: public IEntity
    {
    public:
        Camera();
        ~Camera();

        void Initialise() override;
        void Update() override;
        void Draw() override;
    };
}