
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "event/IdHolder.h"
#include <unordered_map>

class Keyboard{
public:
    /**
     * @brief keyboard keys
     */
    enum class Key{
        A , B, C,
        D, E, F, G,
        H, I, J, K,
        L, M, N, O,
        P, Q, R, S,
        T, U, V, W,
        X, Y, Z, Num0,
        Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8,
        Num9, Escape, LControl, LShift,
        LAlt, LSystem, RControl, RShift,
        RAlt, RSystem, Menu, LBracket,
        RBracket, Semicolon, Comma, Period,
        Quote, Slash, Backslash, Tilde,
        Equal, Hyphen, Space, Enter,
        Backspace, Tab, PageUp, PageDown,
        End, Home, Insert, Delete,
        Add, Subtract, Multiply, Divide,
        Left, Right, Up, Down,
        Numpad0, Numpad1, Numpad2, Numpad3,
        Numpad4, Numpad5, Numpad6, Numpad7,
        Numpad8, Numpad9, F1, F2,
        F3, F4, F5, F6,
        F7, F8, F9, F10,
        F11, F12, F13, F14,
        F15, Pause
    };

    /**
     * @brief Check if key is pressed or not.
     * @param key Key to check.
     * @return true if key is pressed, false if it not pressed.
     *
     * A key is considered pressed if it currently pressed but it was
     * not pressed prior to function call
     */
    static bool isKeyPressed(Key key);

private:
    //Holds the state of a key when it was last checked
    inline static std::unordered_map<Key, bool> prevKeyStateMap_{};
};

#endif