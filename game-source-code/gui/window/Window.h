/**
 * @brief Window that can serve as a target for 2D drawing
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "common/Common.h"
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
         * @brief Check if the event queue is empty or not.
         * @param event Event queue to be checked
         * @return true if event queue is not empty, false if it is empty
         */
        bool pollEvent(sf::Event &event);

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
         * @brief Destructor. Ensures a new Window instance can be created
         *        when an existing Window instance is destroyed
         */
        ~Window();

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
    };
}

#endif