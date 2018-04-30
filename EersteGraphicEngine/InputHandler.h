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

    enum class InputHandlerSwitchedState
    {
        YES, NO
    };

    struct InputMap
    {
        Key* KeyPtr;
        String Handler;
        JoypadButton* ButtonPtr;
        InputHandlerState State;
        InputHandlerSwitchedState Switched;

        InputMap(const String& handler)
            : KeyPtr(nullptr)
            , ButtonPtr(nullptr)
            , Handler(handler)
            , State(InputHandlerState::RELEASED)
            , Switched(InputHandlerSwitchedState::NO)
        {}

        InputMap(Key* key, JoypadButton* button, const String& handler)
            : KeyPtr(key)
            , ButtonPtr(button)
            , Handler(handler)
            , State(InputHandlerState::RELEASED)
            , Switched(InputHandlerSwitchedState::NO)
        {}

        bool operator==(const InputMap& inputMap) const
        {
            return inputMap.Handler == Handler;
        }
    };

    struct InputState
    {
        InputHandlerState State;
        InputHandlerSwitchedState Switched;

        InputState()
            : State(InputHandlerState::RELEASED)
            , Switched(InputHandlerSwitchedState::NO)
        {}

        InputState(const InputMap& map)
            : State(map.State)
            , Switched(map.Switched)
        {}
    };

    class InputHandler : public IModule<InputHandler>, public IComponent, public IComponentHandler
    {
    public:
        InputHandler();
        ~InputHandler() {}
        const InputState GetState(const String& handler);

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