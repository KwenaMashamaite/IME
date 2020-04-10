/**
 * @brief Window that can serve as a target for 2D drawing
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "common/Common.h"
#include "event/EventEmitter.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Gui {
    using Common::Position;
    using Common::Dimensions;

    class Window : sf::NonCopyable {
    public:
        /**
         * @brief Default constructor. Ensures only a single
         *         instance of the class can exist at a time
         */
        Window();

        /**
         * @brief Create a render window
         * @param name Name of the render window
         * @param width Width of the window
         * @param height Height of the window
         *
         * The dimensions of the window must be greater than the
         * minimum dimensions of 100x100 pixels, otherwise the
         * program will be terminated (prematurely). The created
         * window has a maximum frame limit of 60 FPS and V-Sync
         * is enabled by default
         */
        void create(const std::string &name, float width, float height);

        /**
         * @brief Get the dimensions of the window
         * @return Dimensions of the window
         */
        static Dimensions getDimensions(){ return dimensions_;}

        /**
         * @brief Check if the window is open or not
         * @return true if open, false if not open
         */
        bool isOpen() const;

        /**
         * @brief Process events
         *
         * This function will notify event listeners if any events have been
         * captured by the window. An invocation of this function wil empty
         * the event queue
         */
        void processEvents();

        /**
         * @brief Close the window
         */
        void close();

        /**
         * @brief Draw drawable object on the screen
         * @param drawable Object to draw
         */
        void draw(const auto &drawable) {
            window_.draw(drawable);
        }

        /**
         * @brief Display drawn objects on the window
         */
        void display();

        /**
         * @brief Clear the entire window with a single colour
         * @param colour Colour to clear window with
         */
        void clear(sf::Color colour = sf::Color::Black);

        /***
         * @brief Get the mouse cursor position relative to this window
         * @return Mouse cursor position relative to this window
         */
        Position getMouseCursorPosition() const;

        /**
         * @brief Add a listener to a window event
         * @tparam Args Template parameter pack name
         * @param event Event to add listener to
         * @param callback Function to execute when the event is fired
         * @return listener's identification number
         */
        template <typename ...Args>
        static int addListener(const std::string& event, Callback<Args...> callback){
            eventEmitter_.addListener(event, callback);
        }

        /**
         * @brief Remove a listener from a window event
         * @param event Event to remove listener from
         * @param listenerId Identification number of the listener to be removed
         * @return True if a listener was removed from an event, false if the specified
         *         event does not have a listener with the specified id
         */
        static bool removeListener(const std::string& event, int callbackId){
            eventEmitter_.removeListener(event, callbackId);
        }

        /**
         * @brief Destructor. Ensures a new Window instance can be created
         *        when an existing Window instance is destroyed
         */
        ~Window();

    private:
        /**
         * @brief Subscribe to events
         */
        void subscribeToEvents();

    private:
        //SFML render window.
        sf::RenderWindow window_;
        //Dimensions of the window
        static Dimensions dimensions_;
        //Instantiation state
        inline static auto isInstantiated_ = false;
        //Minimum window width
        inline static const auto minWidth = 100u;
        //Minimum window height
        inline static const auto minHeight = 100u;
        //Event Emitter
        inline static EventEmitter eventEmitter_{};
    };
}

#endif