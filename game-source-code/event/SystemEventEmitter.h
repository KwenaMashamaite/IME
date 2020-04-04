/**
 * @brief A class for publishing system events
 *
 * These events are :
 *
 * 1. closed               - Fired when a request to close the application window is made.
 *                           Passes no arguments on notify
 *
 * 2. keyPressed           - Fired when a key is pressed. Passes the key (Keyboard::Key)
 *                           that was pressed as an argument on notify
 *
 * 3. keyReleased          - Fired when a key is released. Passes the key (Keyboard::Key)
 *                           that was released as an argument on notify
 *
 * 4. mouseMoved           - Fired when the mouse is moved. Passes the x and y coordinate
 *                           of the mouse cursor as arguments on notify (int, int)
 *
 * 5. mouseButtonPressed   - Fired when a mouse button is pressed. Passes the button
 *                            (Mouse::Button) that was pressed as an argument on notify
 *
 * 6. mouseButtonReleased  - Fired when a mouse button is released. Passes the button
 *                           (Mouse::Button) that was released as an argument on notify
 *
 * @note When adding listeners to an event, the the parameters of the callback function must
 *       match exactly with the arguments an event provides on notify, otherwise the function
 *       will never be called when the event is raised. In addition, if an event listener is
 *       added to an event that's none of the above events, that event will never be raised,
 *       and consequently the callback will never be invoked
 */

#ifndef SYSTEMEVENTEMITTER_H
#define SYSTEMEVENTEMITTER_H

#include "EventEmitter.h"
#include "gui/window/Window.h"

class SystemEventEmitter : public EventEmitter{
public:
    /**
     * @brief Constructor
     * @param window Render target
     */
    explicit SystemEventEmitter(Gui::Window& window);

    /**
     * @brief Process system events
     *
     * This function will notify event listeners if any events have been
     * captured by the system. @not An invocation of this function wil empty
     * the system event queue. All instances of the class share the same event
     * queue. This means that, if one instance calls this function, then the event
     * queue will be processed for all instances. However, only event listeners
     * registered with the instance that invoked the function will be notified
     */
    void processEvents();

private:
    /**
     * @brief Make function private so that events cannot be emitted externally
     */
    using EventEmitter::emit;

    //Reference to a render target
    Gui::Window& renderTarget_;
};

#endif
