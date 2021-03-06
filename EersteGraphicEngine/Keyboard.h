#pragma once

#include "PrerequisitesCore.h"
#include "IComponent.h"

namespace ege
{
    enum class KeyName
    {
        A, Z, E, R, T, Y, U, I, O, P, Q, S, D, F, G, H, J, K, L, M, W, X, C, V, B, N,
        SPACE, ESCAPE, CTRL, SHIFT, CAPS_LOCK, TAB, ALT, ALT_GR, BACK, ENTER, REMOVE, INSERT, 
        END, PAGE_UP, PAGE_DOWN, PRINT_SCREEN, ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN,
        NUMPAD_0, NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, NUMPAD_6, NUMPAD_7, NUMPAD_8, 
        NUMPAD_9, MULTIPLY, ADD, SUBTRACT, SEPARATOR, DIVIDE, DECIMAL, NUMLOCK,
        NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
    };

    enum class KeyState
    {
        TRIGGERED, RELEASED
    };

    struct Key
    {
        KeyName          Name;
        String           Label;
        UINT             Value;
        KeyState         State;

        Key(KeyName name, const String& label, UINT value)
            : Name(name)
            , Value(value)
            , Label(label)
            , State(KeyState::RELEASED)
        {}

        bool operator==(const Key& key) const
        {
            return key.Name == Name;
        }

        bool operator==(const KeyName& name) const
        {
            return name == Name;
        }

        bool operator==(const String& label) const
        {
            return label == Label;
        }
    };

    class Keyboard : public IModule<Keyboard>, public IComponent
    {
    public:
        Keyboard();
        ~Keyboard() {}
        void            Update(MSG* message);
        Key&            GetKey(const KeyName& name);
        Key&            GetKey(const String& label);
        const KeyState& GetState(const KeyName& name) const;
        const KeyState& GetState(const String& label) const;        

    protected:
        void UpdateState(Key* key, MSG* message);

        void OnStartUp() override;
        void OnShutDown() override {};

    protected:
        Vector<Key> _keys;
    };

    Keyboard&      gKeyboard();
    SPtr<Keyboard> gKeyboardPtr();
}