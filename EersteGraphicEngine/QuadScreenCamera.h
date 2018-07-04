#pragma once

#include "PrerequisitesCore.h"
#include "OrthographicCamera.h"

namespace ege
{
    class QuadScreenCamera : public OrthographicCamera
    {
    public:
        QuadScreenCamera();
        ~QuadScreenCamera();

        void         Update() override;
        virtual void ComputeProjectionMatrix() override;
    };
}