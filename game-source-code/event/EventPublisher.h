/**
 * @brief class for publishing predefined events.
 *
 * This class publishes common events such as mouse click, mouse move,
 * key pressed ,etc when they take place. These events are defined in
 * the global namespace. Therefore, in order to be notified when these
 * events take place a callback function must be registered with the
 * event of interest in the global namespace.
 */

#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include "gui/window/Window.h"

class EventPublisher{
public:
    /**
     * @brief Fires/Raises an event if any.
     *
     * This function has to be called at least once per frame in order
     * to check if any events are to be published, otherwise events
     * that take place will never be raised. That is, event handlers
     * of an event that has taken place will never be invoked/executed.
     */
    static void update(Gui::Window &renderTarget);
};

#endif