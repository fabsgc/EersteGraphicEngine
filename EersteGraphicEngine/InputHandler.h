#pragma once

#include "IComponentHandler.h"
#include "CoreApplication.h"
#include "IComponent.h"
#include "Keyboard.h"
#include "Joypad.h"
#include "Time.h"

namespace ege
{
    enum class InputHandlerState
    {
        TRIGGERED, RELEASED
    };

    struct InputMap
    {
        Key* KeyPtr;
        String Handler;
        JoypadButton* ButtonPtr;
        InputHandlerState State;

        InputMap(const String& handler)
            : KeyPtr(nullptr)
            , ButtonPtr(nullptr)
            , Handler(handler)
            , State(InputHandlerState::RELEASED)
        {}

        InputMap(Key* key, JoypadButton* button, const String& handler)
            : KeyPtr(key)
            , ButtonPtr(button)
            , Handler(handler)
            , State(InputHandlerState::RELEASED)
        {}

        bool operator==(const InputMap& inputMap) const
        {
            return inputMap.Handler == Handler;
        }
    };

    class InputHandler : public IModule<InputHandler>, public IComponent, public IComponentHandler
    {
    public:
        InputHandler();
        ~InputHandler() {}
        const InputHandlerState GetState(const String& handler);

    private:
        void Update(InputMap* inputMap);
        void OnStartUp() override;
        void OnShutDown() override {};

    private:
        Map<Context, Vector<InputMap>> _handlers;
    };

    InputHandler&      gInputHandler();
    SPtr<InputHandler> gInputHandlerPtr();
}