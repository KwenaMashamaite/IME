/**
 * @brief Class for capturing and handling mouse inputs
 */

#ifndef MOUSE_H
#define MOUSE_H

#include "event/EventEmitter.h"

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
     *
     * This function checks the state of a mouse button in real time
    */
    static bool isButtonPressed(Button button);

    /**
     * @brief Add an event listener to a mouse up event
     * @param button Mouse button to listen for
     * @param callback Function to execute when mouse button is released
     * @return Event listeners identification number
     *
     * A mouse up event only occurs for the right and middle mouse button
     */
    static int onButtonUp(Button button, Callback<> callback);

    /**
     * @brief Add an event listener to mouse down event
     * @param button Mouse button to listen for
     * @param callback Function to execute when mouse button is down
     * @return Event listeners identification number
     *
     * A mouse down event only occurs when the mouse button is pressed and
     * released immediately. If the button is not released immediately, a
     * mouse held event will be generated @see onMouseHeld(Callback)
     */
    static int onButtonDown(Button button, Callback<> callback);

    /**
     * @brief Add an event listener to a mouse held event
     * @param button Button to listen for
     * @param callback Function to execute when the mouse button is held
     * @return Event listeners identification number
     *
     * A mouse down event always occurs before a mouse held event. The mouse
     * held event occurs if the mouse button remains down after the first
     * mouse down event and will continue to fire as long as the mouse button
     * remains down
     */
    static int onMouseHeld(Button button, Callback<> callback);

    /**
     * @brief Add an event listener to a mouse click event
     * @param callback Function to execute when mouse is clicked
     * @return Event listeners identification number
     *
     * A click event only occurs after the left mouse button is released
     */
    static int onMouseClick(Callback<> callback);

    /**
     * @brief Add an event listener to a mouse move event
     * @param callback Function to execute when the mouse moves
     * @return Event listeners identification number
     *
     * The callback function will be invoked with the new position (int, int)
     * of the mouse cursor
     */
    static int onMouseMove(Callback<int, int> callback);

    /**
      * @brief  Remove an event listener from an event
      * @param  event Event to remove listener from
      * @param  button Mouse button to remove event listener from
      * @param  listenerId Identification number of the listener to be removed
      * @return True if a listener was removed from an event, false if the
      *         specified event does not have a listener with the specified id
      */
    static bool removeEventListener(const std::string& event, Button button, int listenerId);

private:
    /**
     * @brief Initialize the event emitter for event publishing
     */
    static void initEventEmitter();

private:
    //Holds the last state of a button
    inline static std::unordered_map<Button, bool> prevButtonStateMap_{};
    //Event Emitter/publisher
    inline static EventEmitter eventEmitter_{};
    //State of the event emitter (Since class can be used without instance)
    inline static auto isEventEmitterInitialized_{false};
};

#endif