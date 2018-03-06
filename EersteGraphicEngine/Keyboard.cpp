#include "Keyboard.h"

namespace ege
{
    Keyboard::Keyboard()
        : IComponent(ComponentType::KEYBOARD)
    {
    }

    void Keyboard::Update(MSG* message)
    {
        for (auto key = _keys.begin(); key != _keys.end(); key++)
        {
            if ((*key).Value == message->wParam)
            {
                UpdateState(&(*key), message);
            }
        }
    }

    void Keyboard::UpdateState(Key* key, MSG* message)
    {
        switch (message->message)
        {
        case WM_KEYUP: {
            key->State = KeyState::RELEASED;
        }break;

        case WM_KEYDOWN: {
            key->State = KeyState::TRIGGERED;
        }break;
        }
    }

    KeyState& Keyboard::GetState(const KeyName& name)
    {
        if (std::find(_keys.begin(), _keys.end(), name) != _keys.end())
        {
            for (auto it = _keys.begin(); it != _keys.end(); it++)
            {
                if (*it == name) return it->State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "Key does not exist");
        }

        return _keys.begin()->State;
    }

    KeyState& Keyboard::GetState(const String& label)
    {
        if (std::find(_keys.begin(), _keys.end(), label) != _keys.end())
        {
            for (auto it = _keys.begin(); it != _keys.end(); it++)
            {
                if (*it == label) return it->State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, ("Key does not exist (" + label + ")"));
        }

        return _keys.begin()->State;
    }

    Key& Keyboard::GetKey(const KeyName& name)
    {
        if (std::find(_keys.begin(), _keys.end(), name) != _keys.end())
        {
            for (auto it = _keys.begin(); it != _keys.end(); it++)
            {
                if (*it == name) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "Key does not exist");
        }

        return *_keys.begin();
    }

    Key& Keyboard::GetKey(const String& label)
    {
        if (std::find(_keys.begin(), _keys.end(), label) != _keys.end())
        {
            for (auto it = _keys.begin(); it != _keys.end(); it++)
            {
                if (*it == label) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, ("Key does not exist (" + label + ")"));
        }

        return *_keys.begin();
    }

    void Keyboard::OnStartUp()
    {
        _keys.push_back(Key(KeyName::A, "A", 0x41));
        _keys.push_back(Key(KeyName::Z, "Z", 0x5A));
        _keys.push_back(Key(KeyName::E, "E", 0x45));
        _keys.push_back(Key(KeyName::R, "R", 0x52));
        _keys.push_back(Key(KeyName::T, "T", 0x54));
        _keys.push_back(Key(KeyName::Y, "Y", 0x59));
        _keys.push_back(Key(KeyName::U, "U", 0x55));
        _keys.push_back(Key(KeyName::I, "I", 0x49));
        _keys.push_back(Key(KeyName::O, "O", 0x4F));
        _keys.push_back(Key(KeyName::P, "P", 0x50));
        _keys.push_back(Key(KeyName::Q, "Q", 0x51));
        _keys.push_back(Key(KeyName::R, "R", 0x52));
        _keys.push_back(Key(KeyName::S, "S", 0x53));
        _keys.push_back(Key(KeyName::D, "D", 0x44));
        _keys.push_back(Key(KeyName::F, "F", 0x46));
        _keys.push_back(Key(KeyName::G, "G", 0x47));
        _keys.push_back(Key(KeyName::H, "H", 0x48));
        _keys.push_back(Key(KeyName::J, "J", 0x4A));
        _keys.push_back(Key(KeyName::K, "K", 0x4B));
        _keys.push_back(Key(KeyName::L, "L", 0x4C));
        _keys.push_back(Key(KeyName::M, "M", 0x4D));
        _keys.push_back(Key(KeyName::W, "W", 0x57));
        _keys.push_back(Key(KeyName::X, "X", 0x58));
        _keys.push_back(Key(KeyName::C, "C", 0x43));
        _keys.push_back(Key(KeyName::V, "V", 0x56));
        _keys.push_back(Key(KeyName::B, "B", 0x42));
        _keys.push_back(Key(KeyName::N, "N", 0x4E));

        _keys.push_back(Key(KeyName::SPACE, "SPACE", VK_SPACE));
        _keys.push_back(Key(KeyName::ESCAPE, "ESCAPE", VK_ESCAPE));
        _keys.push_back(Key(KeyName::CTRL, "CTRL", VK_CONTROL));
        _keys.push_back(Key(KeyName::SHIFT, "SHIFT", VK_SHIFT));
        _keys.push_back(Key(KeyName::CAPS_LOCK, "CAPS_LOCK", VK_CAPITAL));
        _keys.push_back(Key(KeyName::TAB, "TAB", VK_TAB));
        _keys.push_back(Key(KeyName::ALT, "ALT", VK_MENU));
        _keys.push_back(Key(KeyName::BACK, "BACK", VK_BACK));
        _keys.push_back(Key(KeyName::ENTER, "ENTER", VK_RETURN));
        _keys.push_back(Key(KeyName::REMOVE, "REMOVE", VK_DELETE));
        _keys.push_back(Key(KeyName::INSERT, "INSERT", VK_INSERT));

        _keys.push_back(Key(KeyName::END, "END", VK_END));
        _keys.push_back(Key(KeyName::PAGE_UP, "PAGE_UP", VK_PRIOR));
        _keys.push_back(Key(KeyName::PAGE_DOWN, "PAGE_DOWN", VK_NEXT));
        _keys.push_back(Key(KeyName::PRINT_SCREEN, "PRINT_SCREEN", VK_SNAPSHOT));

        _keys.push_back(Key(KeyName::ARROW_LEFT, "ARROW_LEFT", VK_LEFT));
        _keys.push_back(Key(KeyName::ARROW_RIGHT, "ARROW_RIGHT", VK_RIGHT));
        _keys.push_back(Key(KeyName::ARROW_UP, "ARROW_UP", VK_UP));
        _keys.push_back(Key(KeyName::ARROW_DOWN, "ARROW_DOWN", VK_DOWN));

        _keys.push_back(Key(KeyName::NUMPAD_0, "NUMPAD_0", VK_NUMPAD0));
        _keys.push_back(Key(KeyName::NUMPAD_1, "NUMPAD_1", VK_NUMPAD1));
        _keys.push_back(Key(KeyName::NUMPAD_2, "NUMPAD_2", VK_NUMPAD2));
        _keys.push_back(Key(KeyName::NUMPAD_3, "NUMPAD_3", VK_NUMPAD3));
        _keys.push_back(Key(KeyName::NUMPAD_4, "NUMPAD_4", VK_NUMPAD4));
        _keys.push_back(Key(KeyName::NUMPAD_5, "NUMPAD_5", VK_NUMPAD5));
        _keys.push_back(Key(KeyName::NUMPAD_6, "NUMPAD_6", VK_NUMPAD6));
        _keys.push_back(Key(KeyName::NUMPAD_7, "NUMPAD_7", VK_NUMPAD7));
        _keys.push_back(Key(KeyName::NUMPAD_8, "NUMPAD_8", VK_NUMPAD8));
        _keys.push_back(Key(KeyName::NUMPAD_9, "NUMPAD_9", VK_NUMPAD9));
        _keys.push_back(Key(KeyName::MULTIPLY, "MULTIPLY", VK_MULTIPLY));
        _keys.push_back(Key(KeyName::ADD, "ADD", VK_ADD));
        _keys.push_back(Key(KeyName::SUBTRACT, "SUBTRACT", VK_SUBTRACT));
        _keys.push_back(Key(KeyName::SEPARATOR, "SEPARATOR", VK_SEPARATOR));
        _keys.push_back(Key(KeyName::DIVIDE, "DIVIDE", VK_DIVIDE));
        _keys.push_back(Key(KeyName::DECIMAL, "DECIMAL", VK_DECIMAL));
        _keys.push_back(Key(KeyName::NUMLOCK, "NUMLOCK", VK_NUMLOCK));

        _keys.push_back(Key(KeyName::NUM_0, "NUM_0", 0x30));
        _keys.push_back(Key(KeyName::NUM_1, "NUM_1", 0x31));
        _keys.push_back(Key(KeyName::NUM_2, "NUM_2", 0x32));
        _keys.push_back(Key(KeyName::NUM_3, "NUM_3", 0x33));
        _keys.push_back(Key(KeyName::NUM_4, "NUM_4", 0x34));
        _keys.push_back(Key(KeyName::NUM_5, "NUM_5", 0x35));
        _keys.push_back(Key(KeyName::NUM_6, "NUM_6", 0x36));
        _keys.push_back(Key(KeyName::NUM_7, "NUM_7", 0x37));
        _keys.push_back(Key(KeyName::NUM_8, "NUM_8", 0x38));
        _keys.push_back(Key(KeyName::NUM_9, "NUM_9", 0x39));

        _keys.push_back(Key(KeyName::F1, "", VK_F1));
        _keys.push_back(Key(KeyName::F2, "", VK_F3));
        _keys.push_back(Key(KeyName::F3, "", VK_F3));
        _keys.push_back(Key(KeyName::F4, "", VK_F4));
        _keys.push_back(Key(KeyName::F5, "", VK_F5));
        _keys.push_back(Key(KeyName::F6, "", VK_F6));
        _keys.push_back(Key(KeyName::F7, "", VK_F7));
        _keys.push_back(Key(KeyName::F8, "", VK_F8));
        _keys.push_back(Key(KeyName::F9, "", VK_F9));
        _keys.push_back(Key(KeyName::F10, "", VK_F10));
        _keys.push_back(Key(KeyName::F11, "", VK_F11));
        _keys.push_back(Key(KeyName::F12, "", VK_F12));
    }

    void Keyboard::OnShutDown()
    {
    }

    Keyboard& gKeyboard()
    {
        return static_cast<Keyboard&>(Keyboard::Instance());
    }

    SPtr<Keyboard> gKeyboardPtr()
    {
        return ege_shared_ptr(static_cast<Keyboard*>(Keyboard::InstancePtr()));
    }
}