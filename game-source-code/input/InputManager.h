/**
 * @brief Class for managing user keyboard and mouse button inputs.
 *
 * This class depends on the EventPublisher class. Therefore, an
 * event publisher must be running in order to process the right
 * user inputs.
 */

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <utility>

struct MousePosition {
    int x;
    int y;
};

class InputManager{
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
     * @brief Mouse Buttons
     */
    enum class MouseButton{
        LMouseButton,
        RMouseButton,
        MiddleButton
    };

    /**
     * @brief Constructor
     */
    InputManager();

    /**
     * @brief Update the previous state of a key/button with the
     *         the current state.
     *
     * Current state refers to the state (pressed or not) of a key/button
     * before a call to update() and previous state refers to the state of
     * a key/button after a call to update(). For example, if a key is
     * currently pressed, update() is called, and the key is released,
     * then in the previous state the key/button was pressed but in the
     * current state the key/button is released.
     */
    void update();

    /**
     * @brief Check if key is pressed or not.
     * @param key Key to check.
     * @return true if key is pressed, false if it not pressed.
     *
     * A key is considered pressed if it currently pressed but it was
     * not pressed during the last call to update()
     */
    bool isKeyPressed(Key key) const;

    /**
     * @brief Check if a key is currently held or not
     * @param key Key to check
     * @return true if key is held, false if not held
     *
     * A key is considered held if it's currently pressed and it
     * was also pressed during the last call to update()
     */
    bool isKeyHeld(Key key) const;

    /**
    * @brief Check if a mouse button is pressed or not
    * @param button Mouse button to check
    * @return true if mouse button is pressed, false if not pressed
     *
     * Similarly to a key, a mouse button is considered pressed if it's
     * currently pressed and it was released in the previous state
    */
    bool isMouseButtonPressed(MouseButton button) const;

    /**
     * @brief Get mouse cursor coordinates
     * @return Mouse cursor coordinates
     *
     * The mouse coordinates are relative to the current active window
     */
    MousePosition getMouseCoords() const;

    /**
     * @brief Destructor
     */
    ~InputManager();

private:
    //Holds the current state of a key
    std::unordered_map<Key, bool > currentKeyMap_;
    //Holds the previous state of a key
    std::unordered_map<Key, bool > previousKeyMap_;
    //Holds mouse coordinates
    MousePosition mouseCoordinates_;
    //Holds the current state of the mouse buttons
    std::unordered_map<MouseButton, bool> currentMouseButtonState_;
    //Holds the previous state of the mouse buttons
    std::unordered_map<MouseButton, bool> previousMouseButtonState_;

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
     * @brief Set mouse button as pressed
     * @param mouseButton Mouse button to press
     */
    void pressMouse(MouseButton mouseButton);

    /**
     * @brief Set mouse button as released
     * @param mouseButton Mouse button to release
     */
    void releaseMouse(MouseButton mouseButton);

    /**
     * @brief Set the mouse cursor coordinates
     * @param x The x coordinate of the mouse cursor
     * @param y The y coordinate of the mouse cursor
     */
    void setMouseCoordinates(unsigned int x, unsigned int y);

    /**
     * @brief Check if a key was held or not in the previous update
     * @param Key Key to check
     * @return true if key was held, false if it was not held
     */
    bool wasKeyHeld(Key key) const;

    /**
     * @brief Get the state of a key/mousebutton
     * @tparam keyMap Keys/MouseButton container
     * @tparam key The key/mouseButton to get the state of
     *
     * The state depends on the type of key map that is provided as an
     * argument. If the "current" key/mouseButton map is passed in as
     * an argument, it returns true if the key/mouseButton is "PRESSED"
     * and false if the key/mouseButton is not pressed. If the "previous"
     * key/mouseButton map is provided as an argument, then the function
     * returns true if the key/mouseButton was "HELD" and false if the
     * key/mouseButton is not held.
     */
    template <typename T, typename U>
    bool getKeyState(const std::unordered_map<T, bool>& keyMap, U key) const;
};

#endif