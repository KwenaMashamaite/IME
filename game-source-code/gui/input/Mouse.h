/**
 * @brief
 */

#ifndef MOUSE_H
#define MOUSE_H

class Mouse{
public:
    /**
     * @brief Mouse Buttons
     */
    enum class Button{
        Left,
        Right,
        Middle
    };

    /**
    * @brief Check if a mouse button is pressed or not
    * @param button Mouse button to check
    * @return true if mouse button is pressed, false if not pressed
    */
    static bool isButtonPressed(Button button);
};

#endif