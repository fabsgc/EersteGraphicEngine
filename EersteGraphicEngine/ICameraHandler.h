#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    template<typename Camera>
    class ICameraHandler
    {
    public:
        ICameraHandler()
            : _camera(nullptr)
        {}

        ~ICameraHandler()
        {}

        void AttachCamera(SPtr<Camera> camera)
        {
            _camera = camera;
        }

        void DetachCamera()
        {
            _camera = nullptr;
        }

        bool HasCamera() const
        {
            return _camera != nullptr;
        }
        
    protected:
        SPtr<Camera> _camera;
    };
}