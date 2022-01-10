////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_WINDOW_H
#define IME_WINDOW_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/graphics/WindowStyles.h"
#include "IME/graphics/Colour.h"
#include <functional>
#include <string>
#include <memory>

namespace ime {
    ///@internal
    namespace priv {
        class RenderTarget;
    }

    class Texture;

    /**
     * @brief Game window
     */
    class IME_API Window {
    public:
        using Callback = std::function<void()>; // Window callback

        /**
         * @brief Copy constructor
         */
        Window(const Window&) = delete;

        /**
         * @brief Copy assignment operator
         */
        Window& operator=(const Window&) = delete;

        /**
         * @brief Move constructor
         */
        Window(Window&&) = delete;

        /**
         * @brief Move assignment operator
         */
        Window& operator=(Window&&) = delete;

        /**
         * @brief Set the window style
         * @param windowStyle New window style (ime::WindowStyle enumeration)
         *
         * Note that window styles can be combined using bitwise OR combination
         * of ime::WindowStyle enumerations. For example, to create a window
         * that is closable and resizable, you do as follows:
         *
         * @code
         * window.setStyle(ime::WindowStyle::Close | ime::WindowStyle::Resize);
         * @endcode
         *
         * @note Changing the window style will recreate the game window
         *
         * By default, the window style is ime::WindowStyle::Default
         *
         * @see getStyle
         */
        void setStyle(Uint32 windowStyle);

        /**
         * @brief Get the current window style
         * @return The current window style
         *
         * @see setStyle
         */
        Uint32 getStyle() const;

        /**
         * @brief Set the title of the window
         * @param title The new title of the window
         *
         * @see getTitle
         */
        void setTitle(const std::string& title);

        /**
         * @brief Get the title of the window
         * @return The title of the window
         *
         * @see setTitle
         */
        const std::string& getTitle() const;

        /**
         * @brief Set the position of thw window on the screen
         * @param position The new position in pixels
         *
         * @see getPosition
         */
        void setPosition(const Vector2i& position);

        /**
         * @brief Get the position of the window in pixels
         * @return The position of the window in pixels
         *
         * @see setPosition
         */
        Vector2i getPosition() const;

        /**
         * @brief Set the position of the mouse cursor relative to the window
         * @param position The new position of the cursor relative to the window
         *
         * To set the position of the mouse cursor in desktop coordinates, use
         * ime::Mouse::setPosition
         *
         * @see getRelativeMousePosition
         */
        void setRelativeMousePosition(const Vector2i& position);

        /**
         * @brief Get the position of the mouse cursor relative to the window
         * @return The position of the mouse cursor relative to the window
         *
         * To get the position of the mouse cursor in desktop coordinates, use
         * ime::Mouse::getPosition
         *
         * @see setRelativeMousePosition
         */
        Vector2i getRelativeMousePosition() const;

        /**
         * @brief Set the size of the rendering region of the window
         * @param size The new size in pixels
         *
         * If the specified size is less than the minimum required size,
         * it will be capped to the minimum size and if it is greater
         * than the maximum size it will be capped to the maximum size
         *
         * @see setMinSize and setMaxSize
         */
        void setSize(const Vector2u& size);

        /**
         * @brief Get the size of the rendering region of the window
         * @return The size of the window
         *
         * The size doesn't include the titlebar and borders of the window
         *
         * @see setSize
         */
        Vector2u getSize() const;

        /**
         * @brief Set the minimum size of the rendering region of the window
         * @param size The new minimum size
         *
         * Set @a size to Vector2u{0, 0} to remove the min size restriction
         *
         * By default the minimum size is Vector2u{0, 0} (unrestricted)
         *
         * @see setMaxSize, getMaxSize
         */
        void setMinSize(const Vector2u& size);

        /**
         * @brief Get the minimum size of the rendering region of the window
         * @return The minimum size of the window
         *
         * @see setMinSize
         */
        Vector2u getMinSize() const;

        /**
         * @brief Set the maximum size of the rendering region of the window
         * @param size The new maximum size
         *
         * Set @a size to Vector2u{0, 0} to remove the max size restriction
         *
         * By default the maximum size is Vector2u{0, 0} (unrestricted)
         *
         * @see setMinSize, getMaxSize, hasMaxBound
         */
        void setMaxSize(const Vector2u& size);

        /**
         * @brief Get the minimum size of the rendering region of the window
         * @return The minimum size of the window
         *
         * @see setMaxSize
         */
        Vector2u getMaxSize() const;

        /**
         * @brief Check if the window has a minimum size requirement
         * @return True if a minimum size has been set, otherwise false
         *
         * @see hasMaxBound, setMinSize
         */
        bool hasMinBound() const;

        /**
         * @brief Check if the window has a maximum size requirement
         * @return True if a maximum size has been set, otherwise false
         *
         * @see hasMinBound, setMaxSize
         */
        bool hasMaxBound() const;

        /**
         * @brief Get the size of the when viewed in full screen
         * @return The size of the window in full screen mode
         */
        static Vector2u getFullScreenSize() ;

        /**
         * @brief Enable or disable full screen mode
         * @param fullScreen True enable full screen, otherwise false
         *
         * @warning This function must be called after ime::Engine::initialize
         * is called, otherwise undefined behavior
         *
         * By default, the window is not in full screen
         *
         * @see toggleFullScreen and isFullScreen
         */
        void setFullScreen(bool fullScreen);

        /**
         * @brief Check if the window is in full screen mode or not
         * @return True if window is in full screen mode, otherwise false
         *
         * @see setFullScreen
         */
        bool isFullScreen() const;

        /**
         * @brief Switch between full screen and non full screen mode
         *
         * @warning This function must be called after ime::Engine::initialize
         * is called, otherwise undefined behavior
         *
         * By default, the window is not in full screen
         *
         * @see setFullScreen
         */
        void toggleFullScreen();

        /**
         * @brief Show or hide the window
         * @param visible True to show the window or false to hide it
         *
         * By default, the window is shown
         */
        void setVisible(bool visible);

        /**
         * @brief Check if the window is visible or not
         * @return True if it is visible, otherwise false
         *
         * @see setVisible
         */
        bool isVisible() const;

        /**
         * @brief Show or hide the mouse cursor
         * @param visible True to show the mouse cursor, or false to hide it
         *
         * By default, the mouse cursor is visible
         *
         * @see isMouseCursorVisible
         */
        void setMouseCursorVisible(bool visible);

        /**
         * @brief Check if the mouse cursor is visible or not
         * @return True if it is visible, otherwise false
         *
         * @see setMouseCursorVisible
         */
        bool isMouseCursorVisible() const;

        /**
         * @brief Grab or release the mouse cursor
         * @param grabbed True to grab the mouse or false to release it
         *
         * If @a grabbed is set to @a true, then the mouse cursor will no
         * longer be able to leave the bounds of the window. Note that
         * the mouse can only be grabbed if the window has focus
         */
        void setMouseCursorGrabbed(bool grabbed);

        /**
         * @brief Limit the frame rate to a maximum fixed frequency
         * @param limit The new limit in frames per seconds (FPS)
         * @throws InvalidArgument If @a limit is equal to 0
         *
         * @warning The frame rate limit must be greater than 0
         *
         * BY default the frame rate limit is 60 FPS
         */
        void setFrameRateLimit(unsigned int limit);

        /**
         * @brief Get the frame rate limit of the window
         * @return The current frame rate (0 implies no limit)
         */
        unsigned int getFrameRateLimit() const;

        /**
         * @brief Enable or disable vertical synchronization
         * @param vSyncEnable True to enable Vsync or false to disable it
         *
         * Activating vertical synchronization will limit the number
         * of frames displayed to the refresh rate of the monitor.
         * This can avoid some visual artifacts, and limit the framerate
         * to a good value (but not constant across different computers).
         *
         * By default, vertical synchronization is disabled
         */
        void setVerticalSyncEnable(bool vSyncEnable);

        /**
         * @brief Check if vertical synchronization is enabled or not
         * @return True if enabled, otherwise false
         */
        bool isVerticalSyncEnabled() const;

        /**
         * @brief Set the fill colour of the window when it is cleared
         * @param colour The new fill colour
         *
         * By default, the clear fill colour is black
         *
         * @see getClearColour
         */
        void setClearColour(const Colour& colour);

        /**
         * @brief Get the fill colour of the window when it is cleared
         * @return The colour used when clearing the window
         *
         * @see setClearColour
         */
        const Colour& getClearColour() const;

        /**
         * @brief Take a screenshot of the window
         * @return A texture updated with the current content of the window
         *
         * The returned texture has the same size as the window
         *
         * Calling this function when the window is not created leads to
         * undefined behavior
         *
         * @see ime::Engine::initialize
         */
         [[nodiscard]]
        std::unique_ptr<Texture> takeScreenshot();

        /**
         * @brief Take a screenshot of the window and immediately save it to a file
         * @param filename Name of the file to save the screenshot to
         *
         * The format of the image is automatically deduced from the file
         * extension. The supported image formats are bmp, png, tga and jpg.
         * The destination file is overwritten if it already exists
         *
         * @code
         * window.takeScreenshot("images/screenshot.png");
         * @endcode
         *
         * Note that calling this function before the window is created leads
         * to undefined behavior
         *
         * @note This function performs a slow operation
         */
        void takeScreenshot(const std::string& filename);

        /**
         * @brief Close the window
         *
         * Note that closing the window will trigger an engine shutdown
         *
         * @see ime::Engine::quit
         */
        void close();

        /**
         * @brief Add an event lister to a window close event
         * @param callback Function to be execute when a window close event
         *                 is triggered
         *
         * The window close event is triggered when close() is called,
         * when the close window (x) button is clicked or when alt + F4
         * is pressed
         *
         * @note Only one event listener may be registered to this event.
         * This means that when a new event listener is added, the previous
         * one is removed. As a result, adding a window close event listener
         * overwrites the default behavior. To remove the listener pass
         * @a nullptr as the argument
         *
         * By default, the internal handler closes the window and shuts down
         * the engine
         */
        void onClose(const Callback& callback);

        /**
         * @brief Add an event listener to an lose focus event
         * @param callback The function to be executed when the window loses focus
         *
         * Note that only a single event listener may be added to this event.
         * Adding a new event listener automatically destroys the current one
         * if any. Pass @a nullptr as an argument to stop the callback execution.
         *
         * By default, there is no callback registered to this event
         *
         * @see onGainFocus
         */
        void onLoseFocus(const Callback& callback);

        /**
         * @brief Add an event listener to a gain focus event
         * @param callback The function to be executed when the window gains focus
         *
         * Note that only a single event listener may be added to this event.
         * Adding a new event listener automatically destroys the current one
         * if any. Pass @a nullptr as an argument to stop the callback execution.
         *
         * By default, there is no callback registered to this event
         *
         * @see onLoseFocus
         */
        void onGainFocus(const Callback& callback);

        /**
         * @brief Add an event listener to an mouse enter event
         * @param callback The function to be executed when the mouse cursor
         *                 enters the window
         *
         * Note that only a single event listener may be added to this event.
         * Adding a new event listener automatically destroys the current one
         * if any. Pass @a nullptr as an argument to stop the callback execution.
         *
         * By default, there is no callback registered to this event
         *
         * @see onMouseExit
         */
        void onMouseEnter(const Callback& callback);

        /**
         * @brief Add an event listener to a mouse left event
         * @param callback The function to be executed when the mouse cursor
         *                 leaves the window
         *
         * Note that only a single event listener may be added to this event.
         * Adding a new event listener automatically destroys the current one
         * if any. Pass @a nullptr as an argument to stop the callback execution.
         *
         * By default, there is no callback registered to this event
         *
         * @see onMouseEnter
         */
        void onMouseExit(const Callback& callback);

        /**
         * @brief Check if the window is open or not
         * @return True if the window is open, otherwise false
         */
        bool isOpen() const;

    private:
        /**
         * @brief Constructor
         * @param renderTarget Render target
         */
        explicit Window(priv::RenderTarget& renderTarget);

        /**
         * @brief Cap a size withing the window bounds
         * @param size The restricted size
         */
        Vector2u boundSize(const Vector2u& size) const;

        /**
         * @brief Add an event listener to a full screen event
         * @param callback Function to be executed when the window toggles
         *                 full screen
         *
         * Note that only one event listener may be attached to this event
         *
         * By default, there is no full screen listener
         */
        void onFullScreenToggle(const Callback& callback);

        /**
         * @brief Emit the window close event
         */
        void emitCloseEvent();

        /**
         * @brief Emit a focus change event
         * @param isFocused True if the window gained focus, otherwise false
         */
        void emitFocusChange(bool focused);

        /**
         * @brief Emit a mouse cursor event
         * @param entered True if the mouse entered the window or false if
         *                the mouse cursor left the window
         */
        void emitMouseCursor(bool entered);

    private:
        priv::RenderTarget& renderTarget_;   //!< Render target
        Vector2u minSize_;                   //!< The windows smallest size
        Vector2u maxSize_;                   //!< The windows largest size
        Uint32 windowStyle_;                 //!< The current style of the window
        Uint32 windowStyleBeforeFullScreen_; //!< The window style before switching to full screen
        unsigned int frameRateLimit_;        //!< The frame rate limit of the window
        bool isVSyncEnabled_;                //!< A flag indicating whether or not vertical synchronization is enabled
        bool isFullScreen_;                  //!< A flag indicating whether or not the window is full screen
        bool isVisible_;                     //!< A flag indicating whether or not the window is visible
        bool isCursorVisible_;               //!< A flag indicating whether or not the mouse cursor is visible
        Vector2u sizeBeforeFullScreen_;      //!< The size of the window before full screen mode
        Callback onWindowClose_;             //!< Function executed when a request to close the window is received
        Callback onFullScreenToggle_;        //!< Function executed when the window toggles full screen
        Callback onLoseFocus_;               //!< Function executed when the window loses focus
        Callback onGainFocus_;               //!< Function executed when the window gains
        Callback onMouseEnter_;              //!< Function executed when the mouse cursor enters the window
        Callback onMouseExit_;               //!< Function executed when the mouse cursor leaves the window
        Colour clearColour_;                 //!< The fill colour of the window when cleared
        friend class Engine;                 //!< Needs access to constructor
    };
}

#endif //IME_WINDOW_H
