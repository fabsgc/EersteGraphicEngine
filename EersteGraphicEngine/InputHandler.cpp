#include "InputHandler.h"


namespace ege
{
    InputHandler::InputHandler()
        : IComponent(ComponentType::INPUT_HANDLER)
        , _coreApplication(gCoreApplication())
    {
    }

    const InputState InputHandler::GetState(const String& handler)
    {
        for (auto itHandler = _handlers.begin(); itHandler != _handlers.end(); itHandler++)
        {
            const Context& context = itHandler->first;

            if (context.Name == _coreApplication.GetCurrentContext()->Name)
            {
                Vector<InputMap>& inputMaps = itHandler->second;

                for (auto itMap = inputMaps.begin(); itMap != inputMaps.end(); itMap++)
                {
                    if (itMap->Handler == handler)
                    {
                        Update(&*itMap);
                        return InputState(*itMap);
                    }
                }
            }
        }

        EGE_ASSERT_ERROR(false, ("This handler does not exist (" + handler + ")"));

        return InputState();
    }

    void InputHandler::Update(InputMap* inputMap)
    {
        Joypad& joypad = gJoypad();
        bool triggered = true;
        bool switched  = false;

        if (inputMap->KeyPtrs.size() > 0)
        {
            for (auto key : inputMap->KeyPtrs)
            {
                if (key->State == KeyState::RELEASED)
                {
                    triggered = false;
                }
            }
        }

        if (joypad.IsConnected() && inputMap->ButtonPtrs.size() > 0 && triggered == false)
        {
            triggered = true;

            for (auto button : inputMap->ButtonPtrs)
            {
                if (button->State == JoypadButtonState::RELEASED)
                {
                    triggered = false;
                }
            }
        }

        if ((inputMap->State == InputHandlerState::RELEASED && triggered) || (inputMap->State == InputHandlerState::TRIGGERED && !triggered))
        {
            switched = true;
        }

        inputMap->State    = (triggered) ? InputHandlerState::TRIGGERED : InputHandlerState::RELEASED;
        inputMap->Switched = (switched) ? InputHandlerSwitchedState::YES : InputHandlerSwitchedState::NO;
    }

    void InputHandler::OnStartUp()
    {
        InsertComponent(gKeyboard());
        InsertComponent(gJoypad());

        Keyboard& keyboard = static_cast<Keyboard&>(GetComponent(ComponentType::KEYBOARD));
        Joypad& joypad     = static_cast<Joypad&>(GetComponent(ComponentType::JOYPAD));

#ifdef EGE_CONFIG_KEYMAP_FILE
        tinyxml2::XMLDocument document;
        document.LoadFile(EGE_CONFIG_KEYMAP_FILE);

        tinyxml2::XMLElement* contextsElement = document.FirstChildElement("keymap");
        EGE_ASSERT_ERROR((contextsElement != nullptr), "Keymap file malformed");

        for (tinyxml2::XMLElement* contextElement = contextsElement->FirstChildElement("context"); contextElement != nullptr; contextElement = contextElement->NextSiblingElement())
        {
            Context context(contextElement->Attribute("name"));
            Vector<InputMap> inputMaps;

            for (tinyxml2::XMLElement* inputElement = contextElement->FirstChildElement("input"); inputElement != nullptr; inputElement = inputElement->NextSiblingElement())
            {
                String keyLabel    = inputElement->Attribute("key");
                String buttonLabel = inputElement->Attribute("button");
                String handler     = inputElement->Attribute("handler");

                InputMap inputMap(handler);

                if (keyLabel != "")
                {
                    Vector<String> keys = Split(keyLabel, '+');

                    for (auto key : keys)
                    {
                        inputMap.KeyPtrs.push_back(&keyboard.GetKey(key));
                    }
                }

                if (buttonLabel != "")
                {
                    Vector<String> buttons = Split(buttonLabel, '+');
                    
                    for (auto button : buttons)
                    {
                        inputMap.ButtonPtrs.push_back(&joypad.GetJoypadButton(button));
                    }
                }

                inputMaps.push_back(inputMap);
            }

            _handlers[context] = inputMaps;
        }
#else
        EGE_ASSERT_ERROR_SHORT("Keymap file path not found");
#endif
    }

    InputHandler& gInputHandler()
    {
        return static_cast<InputHandler&>(InputHandler::Instance());
    }

    SPtr<InputHandler> gInputHandlerPtr()
    {
        return ege_shared_ptr(static_cast<InputHandler*>(InputHandler::InstancePtr()));
    }
}