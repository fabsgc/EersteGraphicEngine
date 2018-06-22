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
                for (auto itInputHandler = itHandler->second.begin(); itInputHandler != itHandler->second.end(); itInputHandler++)
                {
                    Vector<InputMap>& inputMaps = *itInputHandler;

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
        }

        EGE_ASSERT_ERROR(false, ("This handler does not exist (" + handler + ")"));

        return InputState();
    }

    void InputHandler::Update(InputMap* inputMap)
    {
        Joypad& joypad = gJoypad();
        bool triggered = true;
        bool switched  = false;

        if (inputMap->Keys.size() > 0)
        {
            for (auto combination : inputMap->Keys)
            {
                triggered = true;

                for (auto key : combination.KeyPtrs)
                {
                    if (key->State == KeyState::RELEASED)
                    {
                        triggered = false;
                        break;
                    }
                }

                if (triggered)
                {
                    break;
                }
            }
        }

        if (joypad.IsConnected() && inputMap->Buttons.size() > 0 && triggered == false)
        {
            triggered = true;

            for (auto combination : inputMap->Buttons)
            {
                for (auto button : combination.ButtonPtrs)
                {
                    if (button->State == JoypadButtonState::RELEASED)
                    {
                        triggered = false;
                    }
                }
            }
        }

        if ((inputMap->State == InputHandlerState::RELEASED && triggered) || 
            (inputMap->State == InputHandlerState::TRIGGERED && !triggered))
        {
            switched = true;
        }

        inputMap->State = (triggered) ? InputHandlerState::TRIGGERED : InputHandlerState::RELEASED;
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
                    Vector<String> combinations = Split(keyLabel, ',');
                    for (auto combination : combinations)
                    {
                        Vector<String> keys = Split(combination, '+');
                        KeyCombination keyCombination;

                        for (auto key : keys)
                        {
                            keyCombination.KeyPtrs.push_back(&keyboard.GetKey(key));
                        }

                        inputMap.Keys.push_back(keyCombination);
                    }
                }

                if (buttonLabel != "")
                {
                    Vector<String> combinations = Split(buttonLabel, ',');
                    for (auto combination : combinations)
                    {
                        Vector<String> buttons = Split(combination, '+');
                        JoypadButtonCombination buttonCombination;

                        for (auto button : buttons)
                        {
                            buttonCombination.ButtonPtrs.push_back(&joypad.GetJoypadButton(button));
                        }

                        inputMap.Buttons.push_back(buttonCombination);
                    }                 
                }

                inputMaps.push_back(inputMap);
            }

            _handlers[context].push_back(inputMaps);
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