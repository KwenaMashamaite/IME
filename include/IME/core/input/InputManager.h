/**
 * @brief Class for managing keyboard and mouse inputs
 */

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Keyboard.h"
#include "Mouse.h"

namespace IME {
    namespace Input {
        class InputManager {
        public:
            /**
             * @brief Check if a key is currently pressed or not
             * @param key Key to check
             * @return True if key is pressed, otherwise false
             */
            bool isKeyPressed(Keyboard::Key key) const;

            /**
             * @brief Check if a mouse button is currently pressed or not
             * @param button Mouse button to check
             * @return True if mouse button is pressed, otherwise false
             */
            bool isMouseDown(Mouse::Button button) const;

            /**
             * @brief Add a key listener to a key event
             * @param event Name of the event to add key listener to
             * @param key Key to listen for
             * @param callback Function to execute when the key event is raised
             * @return The event listeners identification number or -1 if the
             *         specified key event is invalid
             */
            int addKeyListener(const std::string& event, Keyboard::Key key, Callback<> callback);

            /**
             * @brief Add a mouse listener to a mouse event
             * @param event Name of the event to add mouse listener to
             * @param button Mouse button to listen for
             * @param callback Function to execute when the mouse event is raised
             * @return The event listeners identification number or -1 if the
             *         specified mouse event is invalid
             */
            int addMouseButtonListener(const std::string& event, Mouse::Button button, Callback<> callback);

            /**
             * @brief Add an event listener to a mouse moved event
             * @param callback Function to execute when the mouse is moved
             * @return The event listeners identification number
             */
            int addMouseMovedListener(Callback<int, int> callback);

            /**
             * @brief Remove a key event listener from a key event
             * @param event Event to remove listener from
             * @param key The key the event listener was listening for
             * @param id The identification number of the event listener
             * @return True if the key listener was removed or false if the
              *        specified event does not have a key listener with the
              *        specified id
             */
            bool removeKeyListener(const std::string& event, Keyboard::Key key, int id);

            /**
             * @brief Remove a mouse event listener from a mouse event
             * @param event Event to remove listener from
             * @param button Button the event listener was listening for
             * @param id Identification number of the event listener
             * @return True if a listener was removed from an event, false if the
              *        specified event does not have a listener with the specified id
             */
            bool removeMouseListener(const std::string& event, Mouse::Button button, int id);

            /**
             * @brief Remove an event listener from a mouse moved event listener
             * @param id Identification number of the mouse move event listener
             * @return True if a listener was removed from an event or false if
              *        the mouse move event does not have a listener with the
              *        specified id
             */
            bool removeMouseMovedListener(int id);

            /**
             * @brief Update the event manager
             * @param event Event
             *
             * @warning This function is crucial to the proper functioning of
             * the input manager, It must be called when handling input so
             * that event listeners are notified. Failure to call this function
             * will result in key event listeners not being called
             */
            void update(sf::Event event);

        private:
            //Managed keyboard
            Keyboard keyboard_;
            //Managed Mouse
            Mouse mouse_;
        };
    } // namespace Input
} // namespace IME

#endif
