
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
     * @brief Construct a new Keyboard object
     */
    Keyboard();

    /**
     * @brief Update the previous state of a key/button with the
     *        the current state.
     *
     * Current state refers to the state (pressed or not) of a key/button
     * before a call to update() and previous state refers to the state of
     * a key/button after a call to update(). For example, if a key is
     * currently pressed, update() is called, and the key is released,
     * then in the previous state the key/button was pressed but in the
     * current state the key/button is released.
     */
    static void update();
    

    /**
     * @brief Check if key is pressed or not.
     * @param key Key to check.
     * @return true if key is pressed, false if it not pressed.
     *
     * A key is considered pressed if it currently pressed but it was
     * not pressed during the last call to update()
     */
    static bool isKeyPressed(Key key);

    /**
     * @brief Check if a key is currently held or not
     * @param key Key to check
     * @return true if key is held, false if not held
     *
     * A key is considered held if it's currently pressed and it
     * was also pressed during the last call to update()
     */
    static bool isKeyHeld(Key key);

    /**
     * @brief Destructor
     */
    ~Keyboard();

private:
    //Holds the current state of a key
    inline static std::unordered_map<Key, bool > currentKeyMap_{};
    //Holds the previous state of a key
    inline static std::unordered_map<Key, bool > previousKeyMap_{};
    //Holds the identification numbers of class event handlers
    Utility::IdHolder handlerIdNumbers_;

private:
    /**
     * @brief Set key as pressed
     * @param key Key to press
     */
    void pressKey(Key key);

    /**
     * @brief Set key as released
     * @param key Key to release
     */
    void releaseKey(Key key);

    /**
     * @brief Check if a key was held or not in the previous update
     * @param Key Key to check
     * @return true if key was held, false if it was not held
     */
    static bool wasKeyHeld(Key key);

    /**
     * @brief Get the state of a key
     *
     * The state depends on the type of key map that is provided 
     * as an argument. If the "current" key map is passed in as
     * an argument, it returns true if the key is "PRESSED"
     * and false if the key is not pressed. If the "previous"
     * key map is provided as an argument, then the function
     * returns true if the key was "HELD" and false if the
     * key is not held.
     */
    static bool getKeyState(const std::unordered_map<Key, bool>& keyMap, Key key);
};

#endif