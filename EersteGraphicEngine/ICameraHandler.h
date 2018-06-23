#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    template<typename T>
    class ICameraHandler
    {
    public:
        ICameraHandler()
            : _camera(nullptr)
        {
            static_assert(std::is_base_of<Camera, T>::value,"T must be a descendant of ege::Camera");
        }

        ~ICameraHandler()
        {}

        void AttachCamera(SPtr<T> camera)
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
        SPtr<T> _camera;
    };
}