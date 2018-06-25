#pragma once

#include "PrerequisitesCore.h"
#include "InputHandler.h"
#include "Keyboard.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"
#include "Camera.h"

namespace ege
{
    template<typename T>
    class ICameraHandler
    {
    public:
        ICameraHandler()
            : _camera(nullptr)
            , _inputHandler(gInputHandler())
            , _keyboard(gKeyboard())
            , _joypad(gJoypad())
            , _mouse(gMouse())
            , _time(gTime())
        {
            static_assert(std::is_base_of<Camera, T>::value, "T must be a descendant of ege::Camera");
            InitialiseCameraHandler();
        }

        virtual void InitialiseCameraHandler()
        {
            if (_camera != nullptr)
            {
                _camera->ComputeProjectionMatrix();
            }
        }

        void AttachCamera(SPtr<T> camera)
        {
            _camera = camera;
            InitialiseCameraHandler();
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
        InputHandler& _inputHandler;
        Keyboard&     _keyboard;
        Joypad&       _joypad;
        Mouse&        _mouse;
        Time&         _time;

        SPtr<T>       _camera;
    };
}